#include "cfdump/classfile_info.hpp"

#include<string>
#include "cfdump/constantpool.hpp"
#include "cfdump/field_info.hpp"
#include "cfdump/method_info.hpp"
#include "cfdump/attribute_info.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/streamwrite.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

ClassFile_info::ClassFile_info(){}
ClassFile_info::ClassFile_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}
ClassFile_info::~ClassFile_info(){
    if(constant_pool != nullptr){delete constant_pool;}
}

void ClassFile_info::ResolveIndexReferences() {
    this_class_index.ResolveRead(constant_pool);
    super_class_index.ResolveRead(constant_pool);
    for(auto iter = interfaces.begin(); iter != interfaces.end(); iter++){
        (*iter).ResolveRead(constant_pool);
    }
    for(auto iter = fields.begin(); iter != fields.end(); iter++){
        (*iter).ResolveIndexReferences(constant_pool);
    }
    for(auto iter = methods.begin(); iter != methods.end(); iter++){
        (*iter).ResolveIndexReferences(constant_pool);
    }
    attribute_table.ResolveIndexReferences(constant_pool);
}

void ClassFile_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err)
{
    header = iou::GetNextBEU32(istr, err);
    if(header != 0xCAFEBABE){err<<"ERROR: .class File Begins With \""<<std::hex<<header<<std::dec<<"\" instead of \"0xCAFEBABE\""<<std::endl;}
         
    minor_version = iou::GetNextBEU16(istr, err);
    major_version = iou::GetNextBEU16(istr, err);
    constant_pool = new ConstantPool(istr, err); 
    attribute_name_index_table.SetFromConstantPool(*constant_pool);
    
    access_flags.ReadFromBinaryStream(istr, err);
    
    this_class_index.read_index = iou::GetNextBEU16(istr, err);
    super_class_index.read_index = iou::GetNextBEU16(istr, err);   
    
    uint16_t interfaces_count = iou::GetNextBEU16(istr, err);
    if(interfaces_count > 0){
        for(int i = 0; i<interfaces_count; i++){
            ConstantPoolReference ref;
            ref.read_index = iou::GetNextBEU16(istr, err);
            interfaces.push_back(ref);
        }
    }   
    uint16_t fields_count = iou::GetNextBEU16(istr, err);
    if(fields_count > 0){
        for(int i = 0; i<fields_count; i++){
            Field_info field;
            field.ReadFromBinaryStream(istr, err);
            fields.push_back(field);
        }
    }
    uint16_t methods_count = iou::GetNextBEU16(istr, err);
    if(methods_count > 0){
        for(int i = 0; i<methods_count; i++){
            Method_info method;
            method.ReadFromBinaryStream(istr, err);
            methods.push_back(method);
        }
    }   
    attribute_table.ReadFromBinaryStream(istr, err);    
    ResolveIndexReferences();
}
void ClassFile_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutBEU32(ostr, header);
    iou::PutBEU16(ostr, minor_version);
    iou::PutBEU16(ostr, major_version);
    constant_pool->WriteToBinaryStream(ostr);
    access_flags.WriteToBinaryStream(ostr);
    iou::PutBEU16(ostr, this_class_index.Index());
    iou::PutBEU16(ostr, super_class_index.Index());
    if(interfaces.size() > 0xFFFF){std::cerr<<"ERROR: Too Many Interfaces To Write!!!"<<std::endl;}
    iou::PutBEU16(ostr, interfaces.size());
    for(auto iter = interfaces.begin(); iter != interfaces.end(); iter++) {
        iou::PutBEU16(ostr, (*iter).Index());
    }
    if(fields.size() > 0xFFFF){std::cerr<<"ERROR: Too Many Fields To Write!!!"<<std::endl;}
    iou::PutBEU16(ostr, fields.size());
    for(auto iter = fields.begin(); iter != fields.end(); iter++) {
        (*iter).WriteToBinaryStream(ostr);
    }
    if(methods.size() > 0xFFFF){std::cerr<<"ERROR: Too Many Methods To Write!!!"<<std::endl;}
    iou::PutBEU16(ostr, methods.size());
    for(auto iter = methods.begin(); iter != methods.end(); iter++) {
        (*iter).WriteToBinaryStream(ostr);
    }
    attribute_table.WriteToBinaryStream(ostr);
}

void ClassFile_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, ".class Version Major", major_version, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, ".class Version Minor", minor_version, formatting);
    
    iou::JSON::WriteJSONObject(ostr, "Constant Pool", *constant_pool, formatting);
    iou::JSON::WriteJSONObject(ostr, "Access Flags", access_flags, formatting);
    
    iou::JSON::WriteJSONUnsigned(ostr, "This Class Index", this_class_index.Index(), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Super Class Index", super_class_index.Index(), formatting);
    
    iou::JSON::WriteJSONUnsigned(ostr, "Number Of Interfaces", interfaces.size(), formatting);
    int i = 0;
    for(auto iter = interfaces.begin(); iter != interfaces.end(); iter++){
        iou::JSON::WriteJSONUnsigned(ostr, (std::string("Interface ")+std::to_string(i)).c_str(), (*iter).Index(), formatting);
        i++;
    }
    i = 0;
    iou::JSON::WriteJSONUnsigned(ostr, "Number Of Fields", fields.size(), formatting);
    for(auto iter = fields.begin(); iter != fields.end(); iter++){
        iou::JSON::WriteJSONObject(ostr, (std::string("Field ")+std::to_string(i)).c_str(), (*iter), formatting);
        i++;
    }
    i = 0;
    iou::JSON::WriteJSONUnsigned(ostr, "Number Of Methods", methods.size(), formatting);
    for(auto iter = methods.begin(); iter != methods.end(); iter++){
        iou::JSON::WriteJSONObject(ostr, (std::string("Method ")+std::to_string(i)).c_str(), (*iter), formatting);
        i++;
    }
    iou::JSON::WriteJSONObject(ostr, "Attributes", attribute_table, formatting, true);
}

}