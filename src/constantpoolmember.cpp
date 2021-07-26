#include "cfdump/constantpoolmember.hpp"

//Utf8_info
int Utf8_info::GetIndexOfTag() const {return 1;}
Utf8_info::Utf8_info(std::istream& istr, std::ostream& err = std::cerr){ReadFromBinaryStream(istr, err);}
Utf8_info::~Utf8_info() {if(data != nullptr){delete data;}}
void Utf8_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    length = iou::GetNextBEU16(istr);
    data = new uint8_t[length+1];
    for(int i = 0; i < length; i++){
        data[i] = iou::GetNextU8(istr);
    }
    data[length] = 0x00;
}
void Utf8_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Length", data, formatting, false);
    //This Should Work For Ascii and some of the BMP, But Will Break Horribly In Extended Unicode
    iou::JSON::WriteJSONString(ostr, "MUTF-8", (char*)data, formatting, true);
}

//Integer_info
int Integer_info::GetIndexOfTag() const {return 3;}
Integer_info::Integer_info(std::istream& istr){ReadFromBinaryStream(istr);}
void Integer_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    static_assert(sizeof(int32_t) <= sizeof(uint32_t));
    uint32_t i = iou::GetNextBEU32(istr);
    memcpy(&value, &i, sizeof(int32_t));
}
void Integer_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONSigned(ostr, "Value", value, formatting, true);
}

//Float_info
int Float_info::GetIndexOfTag() const {return 4;}
Float_info::Float_info(std::istream& istr){ReadFromBinaryStream(istr);}
void Float_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    static_assert(sizeof(float) <= sizeof(uint32_t));
    uint32_t i = iou::GetNextBEU32(istr);
    memcpy(&i, &value, sizeof(float));
}
void Float_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONStreamed(ostr, "Value", value, formatting, true);
}

//Long_info
int Long_info::GetIndexOfTag() const {return 5;}
Long_info::Long_info(std::istream& istr){ReadFromBinaryStream(istr);}

void Long_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    static_assert(sizeof(int64_t) <= sizeof(uint64_t));
    uint64_t i = iou::GetNextBEU64(istr);
    memcpy(&value, &i, sizeof(int64_t));
}
void Long_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONSigned(ostr, "Value", value, formatting, true);
}
int Long_info::NumberOfCPEntriesTaken() const {return 2;}

//Double_info
int Double_info::GetIndexOfTag() const {return 6;}
Double_info::Double_info(std::istream& istr){ReadFromBinaryStream(istr);}

void Double_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    uint64_t i = iou::GetNextBEU64(istr);
    static_assert(sizeof(double) <= sizeof(uint64_t));
    memcpy(&value, &i, sizeof(double));
}
void Double_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONStreamed(ostr, "Value", value, formatting, true);
}
int Double_info::NumberOfCPEntriesTaken() const {return 2;}

//Class_info
int Class_info::GetIndexOfTag() const {return 7;}
Class_info::Class_info(std::istream& istr){ReadFromBinaryStream(istr);}

void Class_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    name_index = iou::GetNextBEU16(istr);
}
void Class_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONStreamed(ostr, "Name Index", name_index, formatting, true);
}

//String_info
int String_info::GetIndexOfTag() const {return 8;}
String_info::String_info(std::istream& istr){ReadFromBinaryStream(istr);}

void String_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    string_index = iou::GetNextBEU16(istr);
}
void String_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "String Index", string_index, formatting, true);
}

//Fieldref_info::
int Fieldref_info::GetIndexOfTag() const {return 9;}
Fieldref_info::Fieldref_info(std::istream& istr){ReadFromBinaryStream(istr);}

void Fieldref_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    class_index = iou::GetNextBEU16(istr);
    nameandtype_index = iou::GetNextBEU16(istr);
}
void Fieldref_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Class Index", class_index, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index, formatting, true);
}

//Methodref_info
int Methodref_info::GetIndexOfTag() const {return 10;}
Methodref_info::Methodref_info(std::istream& istr){ReadFromBinaryStream(istr);}

void Methodref_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    class_index = iou::GetNextBEU16(istr);
    nameandtype_index = iou::GetNextBEU16(istr);
}
void Methodref_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Class Index", class_index, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index, formatting, true);
}

//InterfaceMethodref_info
int InterfaceMethodref_info::GetIndexOfTag() const {return 11;}
InterfaceMethodref_info::InterfaceMethodref_info(std::istream& istr){ReadFromBinaryStream(istr);}

void InterfaceMethodref_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    class_index = iou::GetNextBEU16(istr);
    nameandtype_index = iou::GetNextBEU16(istr);
}
void InterfaceMethodref_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Class Index", class_index, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index, formatting, true);
}

//NameAndType_info
int NameAndType_info::GetIndexOfTag() const {return 12;}
NameAndType_info::NameAndType_info(std::istream& istr){ReadFromBinaryStream(istr);}

void NameAndType_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    name_index = iou::GetNextBEU16(istr);
    descriptor_index = iou::GetNextBEU16(istr);
}
void NameAndType_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Descriptor Index", descriptor_index, formatting, true);
}

//MethodHandle_info
int MethodHandle_info::GetIndexOfTag() const {return 15;}
MethodHandle_info::MethodHandle_info(std::istream& istr){ReadFromBinaryStream(istr);}

void MethodHandle_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    reference_kind = iou::GetNextU8(istr);
    reference_index = iou::GetNextBEU16(istr);
}
void MethodHandle_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Reference Kind", reference_kind, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Reference Index", reference_index, formatting, true);
}

//MethodType_info
int MethodType_info::GetIndexOfTag() const {return 16;}
MethodType_info::MethodType_info(std::istream& istr){ReadFromBinaryStream(istr);}

void MethodType_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    descriptor_index = iou::GetNextBEU16(istr);
}
void MethodType_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Descriptor Index", descriptor_index, formatting, true);
}

//Dynamic_info
int Dynamic_info::GetIndexOfTag() const {return 17;}
Dynamic_info::Dynamic_info(std::istream& istr){ReadFromBinaryStream(istr);}

void Dynamic_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    bootstrap_method_attr_index = iou::GetNextBEU16(istr);
    nameandtype_index = iou::GetNextBEU16(istr);
}
void Dynamic_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Bootstrap Method Attr Index", bootstrap_method_attr_index, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index, formatting, true);
}

//InvokeDynamic_info
int InvokeDynamic_info::GetIndexOfTag() const {return 18;}
InvokeDynamic_info::InvokeDynamic_info(std::istream& istr){ReadFromBinaryStream(istr);}

void InvokeDynamic_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    bootstrap_method_attr_index = iou::GetNextBEU16(istr);
    nameandtype_index = iou::GetNextBEU16(istr);
}
void InvokeDynamic_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Bootstrap Method Attr Index", bootstrap_method_attr_index, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "NameAndType Index", nameandtype_index, formatting, true);
}

//Module_info
int Module_info::GetIndexOfTag() const {return 19;}
Module_info::Module_info(std::istream& istr){ReadFromBinaryStream(istr);}

void Module_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    name_index = iou::GetNextBEU16(istr);
}
void Module_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index, formatting, true);
}

//Package_info
int Package_info::GetIndexOfTag() const {return 20;}
Package_info::Package_info(std::istream& istr){ReadFromBinaryStream(istr);}

void Package_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    name_index = iou::GetNextBEU16(istr);
}
void Package_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index, formatting, true);
}

//UnusuableConstantPoolMember
int UnusuableConstantPoolMember::GetIndexOfTag() const {return -1;}
void UnusuableConstantPoolMember::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {};
void UnusuableConstantPoolMember::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONString(ostr, "Unused", "This Constant Pool Index Is Invalid", formatting, true);
}

//CPMError
int CPMError::GetIndexOfTag() const {return -2;}
CPMError::CPMError(std::istream& istr){ReadFromBinaryStream(istr);}

void CPMError::ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) {
    istr.unget();
    error_index = iou::GetNextU8(istr);
}
void CPMError::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Tag", ConstantPoolMember::GetConstantPoolMemberString(*this), formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Error Index", error_index, formatting, true);
}

//Get CPM
ConstantPoolMember* ConstantPoolMember::GetConstantPoolMember(std::istream& istr, const std::streampos& cf_offset, int* amount_to_increment_pool_index) {
    ConstantPoolMember* r;
    std::streampos curr_pos = istr.tellg();
    switch(iou::GetNextU8(istr)) {
        case 1: {r = new Utf8_info(istr); break;}
        case 3: {r = new Integer_info(istr); break;}
        case 4: {r = new Float_info(istr); break;}
        case 5: {r = new Long_info(istr); break;}
        case 6: {r = new Double_info(istr); break;}
        case 7: {r = new Class_info(istr); break;}
        case 8: {r = new String_info(istr); break;}
        case 9: {r = new Fieldref_info(istr); break;}
        case 10: {r = new Methodref_info(istr); break;}
        case 11: {r = new InterfaceMethodref_info(istr); break;}
        case 12: {r = new NameAndType_info(istr); break;}
        case 15: {r = new MethodHandle_info(istr); break;}
        case 16: {r = new MethodType_info(istr); break;}
        case 17: {r = new Dynamic_info(istr); break;}
        case 18: {r = new InvokeDynamic_info(istr); break;}
        case 19: {r = new Module_info(istr); break;}
        case 20: {r = new Package_info(istr); break;}
        case -1: {r = new UnusuableConstantPoolMember(); break;}
        default: {r = new CPMError(istr); break;}
    }
    *amount_to_increment_pool_index = r->NumberOfCPEntriesTaken();
    r->byteOffsetFromClassFile = curr_pos - cf_offset;
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
        case(19):{return "";}
        case(20):{return "";}
    }
}