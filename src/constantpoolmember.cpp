#include "cfdump/constantpoolmember.hpp"

#include "cfdump/static_assertions.hpp"
#include "iostream-util/json.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/streamwrite.hpp"
#include "cfdump/constantpool.hpp"
#include<cstring>

namespace cfd {

uint16_t ConstantPoolReference::Index() const {
    if((pool == nullptr) || (ptr == nullptr)) {return read_index;}
    else{
        return pool->GetIndexOfMember(ptr);
    }
}
void ConstantPoolReference::ResolveRead(ConstantPool* pool) {
    this->pool = pool;
    this->ptr = pool->GetMemberAtIndex(read_index);
}

void ConstantPoolMember::ResolveIndexReferences(ConstantPool* pool) {}

//Utf8_info
int Utf8_info::GetIndexOfTag() const {return 1;}
Utf8_info::Utf8_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}
void Utf8_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    uint16_t length = iou::GetNextBEU16(istr);
    string.clear();
    for(int i = 0; i < length; i++){
        string.push_back(iou::GetNextU8(istr));
    }
}
void Utf8_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    if(string.length() > (0xFFFF)){std::cerr<<"String Is Too Large!"<<std::endl;}
    iou::PutBEU16(ostr, string.length());
    for(auto iter = string.begin(); iter != string.end(); iter++){
        iou::PutU8(ostr, (*iter));
    }
}
void Utf8_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Length", string.length(), formatting, false);
    //This Should Work For Ascii and most/all of the BMP, But Will Break Horribly In Extended Unicode
    iou::JSON::WriteJSONString(ostr, "MUTF-8", string.c_str(), formatting, true);
}

//Integer_info
int Integer_info::GetIndexOfTag() const {return 3;}
Integer_info::Integer_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}
void Integer_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    static_assert(sizeof(int32_t) <= sizeof(uint32_t));
    uint32_t i = iou::GetNextBEU32(istr);
    memcpy(&value, &i, sizeof(int32_t));
}
void Integer_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU32(ostr, value);
}
void Integer_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONSigned(ostr, "Value", value, formatting, true);
}

//Float_info
int Float_info::GetIndexOfTag() const {return 4;}
Float_info::Float_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}
void Float_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    static_assert(sizeof(float) <= sizeof(uint32_t));
    uint32_t i = iou::GetNextBEU32(istr);
    memcpy(&i, &value, sizeof(float));
}
void Float_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU32(ostr, value);
}
void Float_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONNumber(ostr, "Value", value, formatting, true);
}

//Long_info
int Long_info::GetIndexOfTag() const {return 5;}
Long_info::Long_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Long_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    static_assert(sizeof(int64_t) <= sizeof(uint64_t));
    uint64_t i = iou::GetNextBEU64(istr);
    memcpy(&value, &i, sizeof(int64_t));
}
void Long_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU64(ostr, value);
}
void Long_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONSigned(ostr, "Value", value, formatting, true);
}
int Long_info::NumberOfCPEntriesTaken() const {return 2;}

//Double_info
int Double_info::GetIndexOfTag() const {return 6;}
Double_info::Double_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Double_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    uint64_t i = iou::GetNextBEU64(istr);
    static_assert(sizeof(double) <= sizeof(uint64_t));
    memcpy(&value, &i, sizeof(double));
}
void Double_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU64(ostr, value);
}
void Double_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONNumber(ostr, "Value", value, formatting, true);
}
int Double_info::NumberOfCPEntriesTaken() const {return 2;}

//Class_info
int Class_info::GetIndexOfTag() const {return 7;}
Class_info::Class_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Class_info::ResolveIndexReferences(ConstantPool* pool) {
    name_index.ResolveRead(pool);
}

void Class_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    name_index.read_index = iou::GetNextBEU16(istr);
}void Class_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, name_index.Index());
}
void Class_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index.Index(), formatting, true);
}

//String_info
int String_info::GetIndexOfTag() const {return 8;}
String_info::String_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void String_info::ResolveIndexReferences(ConstantPool* pool) {
    string_index.ResolveRead(pool);
}

void String_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    string_index.read_index = iou::GetNextBEU16(istr);
}
void String_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, string_index.Index());
}
void String_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "String Index", string_index.Index(), formatting, true);
}

//Fieldref_info::
int Fieldref_info::GetIndexOfTag() const {return 9;}
Fieldref_info::Fieldref_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Fieldref_info::ResolveIndexReferences(ConstantPool* pool) {
    class_index.ResolveRead(pool);
    nameandtype_index.ResolveRead(pool);
}

void Fieldref_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    class_index.read_index = iou::GetNextBEU16(istr);
    nameandtype_index.read_index = iou::GetNextBEU16(istr);
}
void Fieldref_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, class_index.Index());
    iou::PutBEU16(ostr, nameandtype_index.Index());
}
void Fieldref_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Class Index", class_index.Index(), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index.Index(), formatting, true);
}

//Methodref_info
int Methodref_info::GetIndexOfTag() const {return 10;}
Methodref_info::Methodref_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Methodref_info::ResolveIndexReferences(ConstantPool* pool) {
    class_index.ResolveRead(pool);
    nameandtype_index.ResolveRead(pool);
}

void Methodref_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    class_index.read_index = iou::GetNextBEU16(istr);
    nameandtype_index.read_index = iou::GetNextBEU16(istr);
}
void Methodref_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, class_index.Index());
    iou::PutBEU16(ostr, nameandtype_index.Index());
}
void Methodref_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Class Index", class_index.Index(), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index.Index(), formatting, true);
}

//InterfaceMethodref_info
int InterfaceMethodref_info::GetIndexOfTag() const {return 11;}
InterfaceMethodref_info::InterfaceMethodref_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void InterfaceMethodref_info::ResolveIndexReferences(ConstantPool* pool) {
    class_index.ResolveRead(pool);
    nameandtype_index.ResolveRead(pool);
}

void InterfaceMethodref_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    class_index.read_index = iou::GetNextBEU16(istr);
    nameandtype_index.read_index = iou::GetNextBEU16(istr);
}
void InterfaceMethodref_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, class_index.Index());
    iou::PutBEU16(ostr, nameandtype_index.Index());
}
void InterfaceMethodref_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Class Index", class_index.Index(), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index.Index(), formatting, true);
}

//NameAndType_info
int NameAndType_info::GetIndexOfTag() const {return 12;}
NameAndType_info::NameAndType_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void NameAndType_info::ResolveIndexReferences(ConstantPool* pool) {
    name_index.ResolveRead(pool);
    descriptor_index.ResolveRead(pool);
}

void NameAndType_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    name_index.read_index = iou::GetNextBEU16(istr);
    descriptor_index.read_index = iou::GetNextBEU16(istr);
}
void NameAndType_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, name_index.Index());
    iou::PutBEU16(ostr, descriptor_index.Index());
}
void NameAndType_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index.Index(), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Descriptor Index", descriptor_index.Index(), formatting, true);
}

//MethodHandle_info
int MethodHandle_info::GetIndexOfTag() const {return 15;}
MethodHandle_info::MethodHandle_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void MethodHandle_info::ResolveIndexReferences(ConstantPool* pool) {
    reference_index.ResolveRead(pool);
}

void MethodHandle_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    reference_kind = iou::GetNextU8(istr);
    reference_index.read_index = iou::GetNextBEU16(istr);
}
void MethodHandle_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutU8(ostr, reference_kind);
    iou::PutBEU16(ostr, reference_index.Index());
}
void MethodHandle_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Reference Kind", reference_kind, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Reference Index", reference_index.Index(), formatting, true);
}

//MethodType_info
int MethodType_info::GetIndexOfTag() const {return 16;}
MethodType_info::MethodType_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void MethodType_info::ResolveIndexReferences(ConstantPool* pool) {
    descriptor_index.ResolveRead(pool);
}

void MethodType_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    descriptor_index.read_index = iou::GetNextBEU16(istr);
}
void MethodType_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, descriptor_index.Index());
}
void MethodType_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Descriptor Index", descriptor_index.Index(), formatting, true);
}

//Dynamic_info
int Dynamic_info::GetIndexOfTag() const {return 17;}
Dynamic_info::Dynamic_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Dynamic_info::ResolveIndexReferences(ConstantPool* pool) {
    bootstrap_method_attr_index.ResolveRead(pool);
    nameandtype_index.ResolveRead(pool);
}

void Dynamic_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    bootstrap_method_attr_index.read_index = iou::GetNextBEU16(istr);
    nameandtype_index.read_index = iou::GetNextBEU16(istr);
}
void Dynamic_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, bootstrap_method_attr_index.Index());
    iou::PutBEU16(ostr, nameandtype_index.Index());
}
void Dynamic_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Bootstrap Method Attr Index", bootstrap_method_attr_index.Index(), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index.Index(), formatting, true);
}

//InvokeDynamic_info
int InvokeDynamic_info::GetIndexOfTag() const {return 18;}
InvokeDynamic_info::InvokeDynamic_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void InvokeDynamic_info::ResolveIndexReferences(ConstantPool* pool) {
    bootstrap_method_attr_index.ResolveRead(pool);
    nameandtype_index.ResolveRead(pool);
}

void InvokeDynamic_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    bootstrap_method_attr_index.read_index = iou::GetNextBEU16(istr);
    nameandtype_index.read_index = iou::GetNextBEU16(istr);
}
void InvokeDynamic_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, bootstrap_method_attr_index.Index());
    iou::PutBEU16(ostr, nameandtype_index.Index());
}
void InvokeDynamic_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Bootstrap Method Attr Index", bootstrap_method_attr_index.Index(), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index.Index(), formatting, true);
}

//Module_info
int Module_info::GetIndexOfTag() const {return 19;}
Module_info::Module_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Module_info::ResolveIndexReferences(ConstantPool* pool) {
    name_index.ResolveRead(pool);
}

void Module_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    name_index.read_index = iou::GetNextBEU16(istr);
}
void Module_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, name_index.Index());
}
void Module_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index.Index(), formatting, true);
}

//Package_info
int Package_info::GetIndexOfTag() const {return 20;}
Package_info::Package_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Package_info::ResolveIndexReferences(ConstantPool* pool) {
    name_index.ResolveRead(pool);
}

void Package_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    name_index.read_index = iou::GetNextBEU16(istr);
}
void Package_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutU8(ostr, GetIndexOfTag());
    iou::PutBEU16(ostr, name_index.Index());
}
void Package_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index.Index(), formatting, true);
}
/*
//UnusuableConstantPoolMember
int UnusuableConstantPoolMember::GetIndexOfTag() const {return -1;}
void UnusuableConstantPoolMember::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {};
void UnusuableConstantPoolMember::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONString(ostr, "Unused", "This Constant Pool Index Is Invalid", formatting, true);
}
*/
//CPMError
int CPMError::GetIndexOfTag() const {return -1;}
CPMError::CPMError(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void CPMError::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    istr.unget();
    error_index = iou::GetNextU8(istr);
}
void CPMError::WriteToBinaryStream(std::ostream& ostr) const {
    std::cerr<<"ERROR: Trying To Write A CPMError Constant Pool Member!"<<std::endl;    
}
void CPMError::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Error Index", error_index, formatting, true);
}

//Get CPM
ConstantPoolMember* ConstantPoolMember::NewConstantPoolMember(std::istream& istr, std::ostream& err) {
    ConstantPoolMember* r;
    switch(iou::GetNextU8(istr, err)) {
        case 1: {r = new Utf8_info(istr, err); break;}
        case 3: {r = new Integer_info(istr, err); break;}
        case 4: {r = new Float_info(istr, err); break;}
        case 5: {r = new Long_info(istr, err); break;}
        case 6: {r = new Double_info(istr, err); break;}
        case 7: {r = new Class_info(istr, err); break;}
        case 8: {r = new String_info(istr, err); break;}
        case 9: {r = new Fieldref_info(istr, err); break;}
        case 10: {r = new Methodref_info(istr, err); break;}
        case 11: {r = new InterfaceMethodref_info(istr, err); break;}
        case 12: {r = new NameAndType_info(istr, err); break;}
        case 15: {r = new MethodHandle_info(istr, err); break;}
        case 16: {r = new MethodType_info(istr, err); break;}
        case 17: {r = new Dynamic_info(istr, err); break;}
        case 18: {r = new InvokeDynamic_info(istr, err); break;}
        case 19: {r = new Module_info(istr, err); break;}
        case 20: {r = new Package_info(istr, err); break;}
        default: {r = new CPMError(istr, err); break;}
    }
    return r;
}
const char* ConstantPoolMember::GetConstantPoolMemberString(const ConstantPoolMember& cpm){
    switch(cpm.GetIndexOfTag()){
        case(1):{return "Utf8_info";}
        case(3):{return "Integer_info";}
        case(4):{return "Float_info";}
        case(5):{return "Long_info";}
        case(6):{return "Double_info";}
        case(7):{return "Class_info";}
        case(8):{return "String_info";}
        case(9):{return "Fieldref_info";}
        case(10):{return "Methodref_info";}
        case(11):{return "InterfaceMethodref_info";}
        case(12):{return "NameAndType_info";}
        case(15):{return "MethodHandle_info";}
        case(16):{return "MethodType_info";}
        case(17):{return "Dynamic_info";}
        case(18):{return "InvokeDynamic_info";}
        case(19):{return "Module_info";}
        case(20):{return "Package_info";}
        default:{return "ERROR";}
    }
}

}