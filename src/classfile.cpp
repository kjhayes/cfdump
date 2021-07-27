#include "cfdump/classfile.hpp"

#include<string>
#include "cfdump/constantpool.hpp"
#include "cfdump/field_info.hpp"
#include "cfdump/method_info.hpp"
#include "cfdump/attribute_info.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

ClassFile::ClassFile(){}
ClassFile::ClassFile(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}
ClassFile::~ClassFile(){
    if(constant_pool != nullptr){delete constant_pool;}
    if(interface_indices != nullptr){delete[] interface_indices;}
    if(fields_info != nullptr){delete[] fields_info;}
    if(methods_info != nullptr){delete[] methods_info;}
    if(attributes_info != nullptr){delete[] attributes_info;}
}
void ClassFile::ReadFromBinaryStream(std::istream& istr, std::ostream& err)
{
    header = iou::GetNextBEU32(istr, err);
    if(header != 0xCAFEBABE){err<<"ERROR: .class File Begins With \""<<std::hex<<header<<std::dec<<"\" instead of \"0xCAFEBABE\""<<std::endl;}
         
    minor_version = iou::GetNextBEU16(istr, err);
    major_version = iou::GetNextBEU16(istr, err);
    constant_pool = new ConstantPool(istr, err); 
    
    access_flags.ReadFromBinaryStream(istr, err);
    
    this_class_index = iou::GetNextBEU16(istr, err);
    super_class_index = iou::GetNextBEU16(istr, err);   
    
    interfaces_count = iou::GetNextBEU16(istr, err);
    
    if(interfaces_count > 0){
        interface_indices = new uint16_t[interfaces_count];
        for(int i = 0; i<interfaces_count; i++){
            interface_indices[i] = iou::GetNextBEU16(istr, err);
        }
    }   
    fields_count = iou::GetNextBEU16(istr, err);
    if(fields_count > 0){
        fields_info = new Field_info[fields_count];
        for(int i = 0; i<fields_count; i++){
            fields_info[i].ReadFromBinaryStream(istr, err);
        }
    }
    methods_count = iou::GetNextBEU16(istr, err);
    if(methods_count > 0){
        methods_info = new Method_info[methods_count];
        for(int i = 0; i<methods_count; i++){
            methods_info[i].ReadFromBinaryStream(istr, err);
        }
    }   
    attributes_count = iou::GetNextBEU16(istr, err);
    if(attributes_count > 0){
        attributes_info = new Attribute_info[attributes_count];
        for(int i = 0; i<attributes_count; i++){
            attributes_info[i].ReadFromBinaryStream(istr, err);
        }
    }
}
void ClassFile::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, ".class Version Major", major_version, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, ".class Version Minor", minor_version, formatting);
    
    iou::JSON::WriteJSONObject(ostr, "Constant Pool", *constant_pool, formatting);
    iou::JSON::WriteJSONObject(ostr, "Access Flags", access_flags, formatting);
    
    iou::JSON::WriteJSONUnsigned(ostr, "This Class Index", this_class_index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Super Class Index", super_class_index, formatting);
    
    iou::JSON::WriteJSONUnsigned(ostr, "Number Of Interfaces", interfaces_count, formatting);
    for(int i = 0; i < interfaces_count; i++){
        iou::JSON::WriteJSONUnsigned(ostr, (std::string("Interface ")+std::to_string(i)).c_str(), interface_indices[i], formatting);
    }
    iou::JSON::WriteJSONUnsigned(ostr, "Number Of Fields", fields_count, formatting);
    for(int i = 0; i < fields_count; i++){
        iou::JSON::WriteJSONObject(ostr, (std::string("Field ")+std::to_string(i)).c_str(), fields_info[i], formatting);
    }
    iou::JSON::WriteJSONUnsigned(ostr, "Number Of Methods", methods_count, formatting);
    for(int i = 0; i < methods_count; i++){
        iou::JSON::WriteJSONObject(ostr, (std::string("Method ")+std::to_string(i)).c_str(), methods_info[i], formatting);
    }
    iou::JSON::WriteJSONUnsigned(ostr, "Number Of Attributes", attributes_count, formatting);
    for(int i = 0; i < attributes_count; i++){
        iou::JSON::WriteJSONObject(ostr, (std::string("Attribute ")+std::to_string(i)).c_str(), attributes_info[i], formatting, (i == (attributes_count-1)));
    }
}

}