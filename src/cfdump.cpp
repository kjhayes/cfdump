#include<cstdlib>
#include<assert.h>
#include<fstream>
#include<iostream>
#include<stdint.h>
#include<cstring>
#include<limits>

static_assert(std::numeric_limits<float>::is_iec559);
static_assert(std::numeric_limits<double>::is_iec559);


class ConstantPoolMember {
public:
    size_t byteOffsetFromClassFile;
    
    virtual int NumberOfCPEntriesTaken() const {return 1;}
    //At Tag Byte
    static ConstantPoolMember* GetConstantPoolMember(std::istream& istr, const std::streampos& cf_offset, int* number_of_cp_entries_taken);
    
    //Past Tag Byte
    virtual void LoadFromStream(std::istream& istr) = 0;
    virtual int GetIndexOfTag() const = 0;
    virtual const char* GetTag() const = 0; 

    virtual void OutputDataRaw(std::ostream&, const char* prefix = "") = 0;    
};
class Utf8_info : public ConstantPoolMember {
public:
    const int index = 1;
    const char* tag = "Utf8_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Utf8_info(std::istream& istr){LoadFromStream(istr);}
    ~Utf8_info() {if(data != nullptr){delete data;}}

    uint16_t length;
    uint8_t* data;
    void LoadFromStream(std::istream& istr) override {
        length = GetNextU16(istr);
        data = new uint8_t[length];
        for(int i = 0; i < length; i++){
            data[i] = GetNextU8(istr);
        }
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Length: "<<length;
        //This Should Work For Ascii and some of the BMP, But Will Break Horribly In Extended Unicode
        ostr<<prefix<<"MUTF-8: ";
        for(int i = 0; i < length; i++){
            ostr<<(unsigned char)data[i];
        }
    }
};
class Integer_info : public ConstantPoolMember {
public:
    const int index = 3;
    const char* tag = "Integer_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Integer_info(std::istream& istr){LoadFromStream(istr);}

    int32_t value;
    void LoadFromStream(std::istream& istr) override {
        static_assert(sizeof(int32_t) <= sizeof(uint32_t));
        uint32_t i = GetNextU32(istr);
        memcpy(&value, &i, sizeof(int32_t));
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Value: "<<value;
    }
};
class Float_info : public ConstantPoolMember {
public:
    const int index = 4;
    const char* tag = "Float_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Float_info(std::istream& istr){LoadFromStream(istr);}
    
    float value;
    void LoadFromStream(std::istream& istr) override {
        static_assert(sizeof(float) <= sizeof(uint32_t));
        uint32_t i = GetNextU32(istr);
        memcpy(&i, &value, sizeof(float));
    }
    
    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Value: "<<value;
    }
};
class Long_info : public ConstantPoolMember {
public:
    const int index = 5;
    const char* tag = "Long_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Long_info(std::istream& istr){LoadFromStream(istr);}
    
    int64_t value;
    void LoadFromStream(std::istream& istr) override {
        static_assert(sizeof(int64_t) <= sizeof(uint64_t));
        uint64_t i = GetNextU64(istr);
        memcpy(&value, &i, sizeof(int64_t));
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Value: "<<value;
    }

    int NumberOfCPEntriesTaken() const override {return 2;}
};
class Double_info : public ConstantPoolMember {
public:
    const int index = 6;
    const char* tag = "Double_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Double_info(std::istream& istr){LoadFromStream(istr);}
    
    double value;
    void LoadFromStream(std::istream& istr) override {
        uint64_t i = GetNextU64(istr);
        static_assert(sizeof(double) <= sizeof(uint64_t));
        memcpy(&value, &i, sizeof(double));
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Value: "<<value;
    }

    int NumberOfCPEntriesTaken() const override {return 2;}
};
class Class_info : public ConstantPoolMember {
public:
    const int index = 7;
    const char* tag = "Class_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Class_info(std::istream& istr){LoadFromStream(istr);}

    uint16_t name_index;
    void LoadFromStream(std::istream& istr) override {
        name_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Name Index: "<<name_index;
    }
};
class String_info : public ConstantPoolMember {
public:
    const int index = 8;
    const char* tag = "String_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    String_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t string_index;
    void LoadFromStream(std::istream& istr) override {
        string_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"String Index: "<<string_index;
    }
};
class Fieldref_info : public ConstantPoolMember {
public:
    const int index = 9;
    const char* tag = "Fieldref_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Fieldref_info(std::istream& istr){LoadFromStream(istr);}

    uint16_t class_index;
    uint16_t nameandtype_index;
    void LoadFromStream(std::istream& istr) override {
        class_index = GetNextU16(istr);
        nameandtype_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Class Index: "<<class_index;
        ostr<<prefix<<"NameAndType Index: "<<nameandtype_index;
    }
};
class Methodref_info : public ConstantPoolMember {
public:
    const int index = 10;
    const char* tag = "Methodref_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Methodref_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t class_index;
    uint16_t nameandtype_index;
    void LoadFromStream(std::istream& istr) override {
        class_index = GetNextU16(istr);
        nameandtype_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Class Index: "<<class_index;
        ostr<<prefix<<"NameAndType Index: "<<nameandtype_index;
    }
};
class InterfaceMethodref_info : public ConstantPoolMember {
public:
    const int index = 11;
    const char* tag = "InterfaceMethodref_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    InterfaceMethodref_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t class_index;
    uint16_t nameandtype_index;
    void LoadFromStream(std::istream& istr) override {
        class_index = GetNextU16(istr);
        nameandtype_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Class Index: "<<class_index;
        ostr<<prefix<<"NameAndType Index: "<<nameandtype_index;
    }
};
class NameAndType_info : public ConstantPoolMember {
public:
    const int index = 12;
    const char* tag = "NameAndType_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    NameAndType_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t name_index;
    uint16_t descriptor_index;
    void LoadFromStream(std::istream& istr) override {
        name_index = GetNextU16(istr);
        descriptor_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Name Index: "<<name_index;
        ostr<<prefix<<"Descriptor Index: "<<descriptor_index;
    }
};
class MethodHandle_info : public ConstantPoolMember {
public:
    const int index = 15;
    const char* tag = "MethodHandle_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    MethodHandle_info(std::istream& istr){LoadFromStream(istr);}
    
    uint8_t reference_kind;
    uint16_t reference_index;
    void LoadFromStream(std::istream& istr) override {
        reference_kind = GetNextU8(istr);
        reference_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Reference Kind: "<<(unsigned int)reference_kind;
        ostr<<prefix<<"Reference Index: "<<reference_index;
    }
};
class MethodType_info : public ConstantPoolMember {
public:
    const int index = 16;
    const char* tag = "MethodType_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    MethodType_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t descriptor_index;
    void LoadFromStream(std::istream& istr) override {
        descriptor_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Descriptor Index: "<<descriptor_index;
    }
};
class Dynamic_info : public ConstantPoolMember {
public:
    const int index = 17;
    const char* tag = "Dynamic_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Dynamic_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t bootstrap_method_attr_index;
    uint16_t nameandtype_index;
    void LoadFromStream(std::istream& istr) override {
        bootstrap_method_attr_index = GetNextU16(istr);
        nameandtype_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Bootstrap Method Attr Index: "<<bootstrap_method_attr_index;
        ostr<<prefix<<"NameAndType Index: "<<nameandtype_index;
    }
};
class InvokeDynamic_info : public ConstantPoolMember {
public:
    const int index = 18;
    const char* tag = "InvokeDynamic_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    InvokeDynamic_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t bootstrap_method_attr_index;
    uint16_t nameandtype_index;
    void LoadFromStream(std::istream& istr) override {
        bootstrap_method_attr_index = GetNextU16(istr);
        nameandtype_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Bootstrap Method Attr Index: "<<bootstrap_method_attr_index;
        ostr<<prefix<<"NameAndType Index: "<<nameandtype_index;
    }
};
class Module_info : public ConstantPoolMember {
public:
    const int index = 19;
    const char* tag = "Module_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Module_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t name_index;
    void LoadFromStream(std::istream& istr) override {
        name_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Name Index: "<<name_index;
    }
};
class Package_info : public ConstantPoolMember {
public:
    const int index = 20;
    const char* tag = "Package_info";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    Package_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t name_index;
    void LoadFromStream(std::istream& istr) override {
        name_index = GetNextU16(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Name Index: "<<name_index;
    }
};

class UnusuableConstantPoolMember : public ConstantPoolMember {
    const int index = 0;
    const char* tag = "Unusable";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    void LoadFromStream(std::istream& istr) override {};
    void OutputDataRaw(std::ostream& ostr, const char* prefix = ""){
        ostr<<prefix<<"N/A";
    }
};

class CPMError : public ConstantPoolMember {
public:
    const int index = -1;
    const char* tag = "Undefined";
    int GetIndexOfTag() const override {return index;}
    const char* GetTag() const override {return tag;}
    CPMError(std::istream& istr){LoadFromStream(istr);}
    
    uint8_t error_index;
    void LoadFromStream(std::istream& istr) override {
        istr.unget();
        error_index = GetNextU8(istr);
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Error: Index \""<<(unsigned int)error_index<<"\" is Undefined! Begins At Byte [0x"<<std::hex<<byteOffsetFromClassFile<<std::dec<<"] From The Beginning Of The Class File!";
    }
};


ConstantPoolMember* ConstantPoolMember::GetConstantPoolMember(std::istream& istr, const std::streampos& cf_offset, int* amount_to_increment_pool_index) {
    ConstantPoolMember* r;
    std::streampos curr_pos = istr.tellg();
    switch(GetNextU8(istr)) {
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
        default: {r = new CPMError(istr); break;}
    }
    *amount_to_increment_pool_index = r->NumberOfCPEntriesTaken();
    r->byteOffsetFromClassFile = curr_pos - cf_offset;
    return r;
} 

class ConstantPool {
private:
    int count;
    int number_of_members;
    ConstantPoolMember** members;
public:
    ConstantPool(std::istream& istr, const std::streampos& cf_offset) {
        count = GetNextU16(istr);
        number_of_members = count-1;
        members = new ConstantPoolMember*[count-1];
        int i = 0;
        int number_of_cp_entries_taken;
        while(i<count-1){
            members[i] = ConstantPoolMember::GetConstantPoolMember(istr, cf_offset, &number_of_cp_entries_taken);
            for(int x = 1; x < number_of_cp_entries_taken; x++){
                members[i+1] = new UnusuableConstantPoolMember();
            }
            i += number_of_cp_entries_taken;
        }
    }
    ~ConstantPool() {
        if(members != nullptr){
            for(int i = 0; i<number_of_members; i++){
                if(members[i] != nullptr) {delete members[i];}
            }
            delete[] members;
        }
    }

    ConstantPoolMember* GetMember_PoolIndex(const int& index) {return members[index-1];}
    ConstantPoolMember* GetMember_ArrayIndex(const int& index) {return members[index];}
    int GetCount() {return count;}
    int GetNumberOfMembers() {return number_of_members;}

    void OutputMembersRaw(std::ostream& ostr, const char* prefix){
        for(int i = 0; i < number_of_members; i++){
            ostr<<prefix<<i+1<<": [0x"<<std::hex<<members[i]->byteOffsetFromClassFile<<std::dec<<"] {Tag: "<<members[i]->GetIndexOfTag()<<" ("<<members[i]->GetTag()<<")";
            members[i]->OutputDataRaw(ostr, ", ");
            ostr<<"}";
        }
    }
};

class Attribute_info {
public:
    Attribute_info(){}
    Attribute_info(std::istream& istr){LoadFromStream(istr);}
    ~Attribute_info() {if(info != nullptr) {delete[] info;}}
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t* info = nullptr;

    void LoadFromStream(std::istream& istr){
        attribute_name_index = GetNextU16(istr);
        attribute_length = GetNextU32(istr);
        if(attribute_length > 0){
            info = new uint8_t[attribute_length];
            for(int i = 0; i<attribute_length; i++){
                info[i] = GetNextU8(istr);
            }
        }
    }

    void OutputDataRaw(std::ostream& ostr, const char* padding = ", "){
        ostr<<"Name Index: "<<attribute_name_index;
        ostr<<padding<<"Length (bytes): "<<attribute_length;
        
        if(info != nullptr){
            ostr<<padding<<"Info (utf-8): \"";
            for(int i = 0; i<attribute_length; i++){
                ostr<<(char)info[i];
            }
            ostr<<"\"";
            ostr<<padding<<"Info (hex bytes): ("<<std::hex;
            for(int i = 0; i<attribute_length; i++){
                ostr<<" 0x"<<(unsigned int)info[i];
            }
            ostr<<std::dec<<" )";
        }
    }
};

class AccessFlags {
public:
    enum FieldAccessFlagsEnum{
        F_PUBLIC = 0x0001,
        F_PRIVATE = 0x0002,
        F_PROTECTED = 0x0004,
        F_STATIC = 0x0008,
        F_FINAL = 0x0010,
        F_VOLATILE = 0x0020,
        F_TRANSIENT = 0x0040,
        F_SYNTHETIC = 0x1000,
        F_ENUM = 0x4000
    };
    static const char* FieldAccessStrings[9];
    static void OutputFieldAccessFlags(std::ostream& ostr, const uint16_t& flags, const char* padding = " "){
        bool has_been_output = false;
    
        if(flags & FieldAccessFlagsEnum::F_ENUM) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[8];has_been_output = true;}
        if(flags & FieldAccessFlagsEnum::F_FINAL) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[4];has_been_output = true;}
        if(flags & FieldAccessFlagsEnum::F_PRIVATE) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[1];has_been_output = true;}
        if(flags & FieldAccessFlagsEnum::F_PROTECTED) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[2];has_been_output = true;}
        if(flags & FieldAccessFlagsEnum::F_PUBLIC) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[0];has_been_output = true;}
        if(flags & FieldAccessFlagsEnum::F_STATIC) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[3];has_been_output = true;}
        if(flags & FieldAccessFlagsEnum::F_SYNTHETIC) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[7];has_been_output = true;}
        if(flags & FieldAccessFlagsEnum::F_TRANSIENT) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[6];has_been_output = true;}
        if(flags & FieldAccessFlagsEnum::F_VOLATILE) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[5];has_been_output = true;}
    }

    enum MethodAccessFlagsEnum{
        M_PUBLIC = 0x0001,
        M_PRIVATE = 0x0002,
        M_PROTECTED = 0x0004,
        M_STATIC = 0x0008,
        M_FINAL = 0x0010,
        M_SYNCHRONIZED = 0x0020,
        M_BRIDGE = 0x0040,
        M_VARARGS = 0x0080,
        M_NATIVE = 0x0100,
        M_ABSTRACT = 0x0400,
        M_STRICT = 0x0800,
        M_SYNTHETIC = 0x1000
    };
    static const char* MethodAccessStrings[12];
    static void OutputMethodAccessFlags(std::ostream& ostr, const uint16_t& flags, const char* padding = " "){
        bool has_been_output = false;
        
        if(flags & MethodAccessFlagsEnum::M_ABSTRACT) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[9];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_BRIDGE) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[6];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_FINAL) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[4];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_NATIVE) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[8];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_PRIVATE) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[1];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_PROTECTED) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[2];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_PUBLIC) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[0];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_STATIC) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[3];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_STRICT) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[10];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_SYNCHRONIZED) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[5];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_SYNTHETIC) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[11];has_been_output = true;}
        if(flags & MethodAccessFlagsEnum::M_VARARGS) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[7];has_been_output = true;}
    }
    enum ClassAccessFlagsEnum {
        C_PUBLIC = 0x0001,
        C_FINAL = 0x0010,
        C_SUPER = 0x0020,
        C_INTERFACE = 0x0200,
        C_ABSTRACT = 0x0400,
        C_SYNTHETIC = 0x1000,
        C_ANNOTATION = 0x2000,
        C_ENUM = 0x4000,
        C_MODULE = 0x8000
    };
    static const char* ClassAccessStrings[9];
    static void OutputClassAccessFlags(std::ostream& ostr, const uint16_t& flags, const char* padding = " ") {
        bool has_been_output = false;
    
        if(flags & ClassAccessFlagsEnum::C_ABSTRACT) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[4];has_been_output = true;}
        if(flags & ClassAccessFlagsEnum::C_ANNOTATION) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[6];has_been_output = true;}
        if(flags & ClassAccessFlagsEnum::C_ENUM) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[7];has_been_output = true;}
        if(flags & ClassAccessFlagsEnum::C_FINAL) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[1];has_been_output = true;}
        if(flags & ClassAccessFlagsEnum::C_INTERFACE) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[3];has_been_output = true;}
        if(flags & ClassAccessFlagsEnum::C_PUBLIC) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[0];has_been_output = true;}
        if(flags & ClassAccessFlagsEnum::C_SUPER) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[2];has_been_output = true;}    
        if(flags & ClassAccessFlagsEnum::C_SYNTHETIC) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[5];has_been_output = true;}
        if(flags & ClassAccessFlagsEnum::C_MODULE) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[8];has_been_output = true;}
    }
};
const char* AccessFlags::FieldAccessStrings[9] = {
    "PUBLIC",       //0
    "PRIVATE",      //1
    "PROTECTED",    //2
    "STATIC",       //3
    "FINAL",        //4
    "VOLATILE",     //5
    "TRANSIENT",    //6
    "SYNTHETIC",    //7
    "ENUM"          //8
};
const char* AccessFlags::MethodAccessStrings[12] = {
    "PUBLIC",       //0
    "PRIVATE",      //1
    "PROTECTED",    //2
    "STATIC",       //3
    "FINAL",        //4
    "SYNCHRONIZED",  //5
    "BRIDGE",       //6
    "VARARGS",      //7
    "NATIVE",       //8
    "ABSTRACT",     //9
    "STRICT",       //10
    "SYNTHETIC"     //11
};
const char* AccessFlags::ClassAccessStrings[9] = {
    "PUBLIC",       //0
    "FINAL",        //1
    "SUPER",        //2
    "INTERFACE",    //3
    "ABSTRACT",     //4
    "SYNTHETIC",    //5
    "ANNOTATION",   //6
    "ENUM",         //7
    "MODULE"        //8
};
    

class Field_info {
    
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    Attribute_info* attributes;

public:
    Field_info(){}
    Field_info(std::istream& istr){LoadFromStream(istr);}
    ~Field_info() {
        if(attributes != nullptr){
            delete[] attributes;
        }
    }

    void LoadFromStream(std::istream& istr){
        access_flags = GetNextU16(istr);
        name_index = GetNextU16(istr);
        descriptor_index = GetNextU16(istr);
        attributes_count = GetNextU16(istr);
        if(attributes_count > 0){
            attributes = new Attribute_info[attributes_count];
            for(int i = 0; i<attributes_count; i++){
                attributes[i].LoadFromStream(istr);
            }
        }
    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix){
        ostr<<prefix<<"Access Flags:(";
        AccessFlags::OutputFieldAccessFlags(ostr, access_flags, " | ");
        ostr<<")";
        ostr<<prefix<<"Name Index: "<<name_index;
        ostr<<prefix<<"Descriptor Index: "<<descriptor_index;
        ostr<<prefix<<"Attributes Count: "<<attributes_count;
        if(attributes_count > 0){
            for(int i = 0; i < attributes_count; i++){
                ostr<<prefix<<"Attribute "<<i<<": {";
                attributes[i].OutputDataRaw(ostr);
                ostr<<"}";
            }
        }
    }
};
class Method_info {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    Attribute_info* attributes;

public:
    Method_info(){}
    Method_info(std::istream& istr){LoadFromStream(istr);}
    ~Method_info() {
        if(attributes != nullptr){
            delete[] attributes;
        }
    }

    void LoadFromStream(std::istream& istr){
        access_flags = GetNextU16(istr);
        name_index = GetNextU16(istr);
        descriptor_index = GetNextU16(istr);
        attributes_count = GetNextU16(istr);
        if(attributes_count > 0){
            attributes = new Attribute_info[attributes_count];
            for(int i = 0; i<attributes_count; i++){
                attributes[i].LoadFromStream(istr);
            }
        }

    }

    void OutputDataRaw(std::ostream& ostr, const char* prefix){
        ostr<<prefix<<"Access Flags:(";
        AccessFlags::OutputMethodAccessFlags(ostr, access_flags, " | ");
        ostr<<")";
        ostr<<prefix<<"Name Index: "<<name_index;
        ostr<<prefix<<"Descriptor Index: "<<descriptor_index;
        ostr<<prefix<<"Attributes Count: "<<attributes_count;
        if(attributes_count > 0){
            for(int i = 0; i < attributes_count; i++){
                ostr<<prefix<<"Attribute "<<i<<": {";
                attributes[i].OutputDataRaw(ostr);
                ostr<<"}";
            }
        }
    }
};

class ClassFile {
public:
    std::streampos beginningStreamPos;

    uint32_t header;
    uint16_t minor_version, major_version;

private:
    ConstantPool* constant_pool;

public:
    uint16_t access_flags;

    uint16_t this_class_index;
    uint16_t super_class_index;

    uint16_t interfaces_count;
    uint16_t* interface_indices = nullptr;

    uint16_t fields_count;
    Field_info* fields_info = nullptr;

    uint16_t methods_count;
    Method_info* methods_info = nullptr;

    uint16_t attributes_count;
    Attribute_info* attributes_info = nullptr;

    ClassFile(){}
    ClassFile(std::istream& istr, std::ostream& err = std::cerr){
        LoadFromStream(istr, err);
    }

    ~ClassFile(){
        if(constant_pool != nullptr){delete constant_pool;}
        if(interface_indices != nullptr){delete[] interface_indices;}
        if(fields_info != nullptr){delete[] fields_info;}
        if(methods_info != nullptr){delete[] methods_info;}
        if(attributes_info != nullptr){delete[] attributes_info;}
    }

    void LoadFromStream(std::istream& istr, std::ostream& err = std::cerr)
    {
        beginningStreamPos = istr.tellg();

        ReadClassHeader(istr, err);
        
        minor_version = GetNextU16(istr);
        major_version = GetNextU16(istr);

        constant_pool = new ConstantPool(istr, beginningStreamPos); 
        
        access_flags = GetNextU16(istr);
        
        this_class_index = GetNextU16(istr);
        super_class_index = GetNextU16(istr);   
        
        interfaces_count = GetNextU16(istr);
        
        if(interfaces_count > 0){
            interface_indices = new uint16_t[interfaces_count];
            for(int i = 0; i<interfaces_count; i++){
                interface_indices[i] = GetNextU16(istr);
            }
        }   
        fields_count = GetNextU16(istr);
        if(fields_count > 0){
            fields_info = new Field_info[fields_count];
            for(int i = 0; i<fields_count; i++){
                fields_info[i].LoadFromStream(istr);
            }
        }
        methods_count = GetNextU16(istr);
        if(methods_count > 0){
            methods_info = new Method_info[methods_count];
            for(int i = 0; i<methods_count; i++){
                methods_info[i].LoadFromStream(istr);
            }
        }   
        attributes_count = GetNextU16(istr);
        if(attributes_count > 0){
            attributes_info = new Attribute_info[attributes_count];
            for(int i = 0; i<attributes_count; i++){
                attributes_info[i].LoadFromStream(istr);
            }
        }
    }

    void SynchronousLoadOutputRaw(std::istream& istr, std::ostream& ostr = std::cout, std::ostream& err = std::cerr) {
        beginningStreamPos = istr.tellg();
        
        ReadClassHeader(istr, err);

        minor_version = GetNextU16(istr);
        major_version = GetNextU16(istr);
        ostr<<".class version: "<<major_version<<"."<<minor_version<<std::endl;
        
        constant_pool = new ConstantPool(istr, beginningStreamPos);
        ostr<<"Constant Pool:"<<std::endl;
        constant_pool->OutputMembersRaw(ostr, "\n\t");

        access_flags = GetNextU16(istr);
        ostr<<std::endl<<"Class Access Flags: {";
        AccessFlags::OutputClassAccessFlags(ostr, access_flags, " | ");
        ostr<<"}"<<std::endl;

        this_class_index = GetNextU16(istr);
        ostr<<"This Class Index: "<<this_class_index<<std::endl;

        super_class_index = GetNextU16(istr);
        ostr<<"Super Class Index: "<<this_class_index<<std::endl;

        interfaces_count = GetNextU16(istr);
        ostr<<"Number of Interfaces: "<<interfaces_count<<std::endl;
        if(interfaces_count > 0){
            interface_indices = new uint16_t[interfaces_count];
            for(int i = 0; i<interfaces_count; i++){
                interface_indices[i] = GetNextU16(istr);
            }
        }
        if(interfaces_count > 0){
            ostr<<"Interface Indices: {"<<interface_indices[0];
            for(int i = 1; i < interfaces_count; i++){
                ostr<<", "<<interface_indices[i];
            }
            ostr<<std::endl;
        }


        fields_count = GetNextU16(istr);
        ostr<<"Number of Fields: "<<fields_count;
        if(fields_count > 0){
            fields_info = new Field_info[fields_count];
            for(int i = 0; i<fields_count; i++){
                fields_info[i].LoadFromStream(istr);
            }
        }
        if(fields_count > 0){
            for(int i = 0; i < fields_count; i++){
                ostr<<std::endl<<"Field "<<i<<": ";
                fields_info[i].OutputDataRaw(ostr, "\n\t");
            }
        }
        ostr<<std::endl<<std::endl;
        
        methods_count = GetNextU16(istr);
        ostr<<"Number of Methods: "<<methods_count;
        if(methods_count > 0){
            methods_info = new Method_info[methods_count];
            for(int i = 0; i<methods_count; i++){
                methods_info[i].LoadFromStream(istr);
            }
        }
        if(methods_count > 0){
            for(int i = 0; i < methods_count; i++){
                ostr<<std::endl<<"Method "<<i<<": ";
                methods_info[i].OutputDataRaw(ostr, "\n\t");
            }
        }
        ostr<<std::endl<<std::endl;

        attributes_count = GetNextU16(istr);
        ostr<<"Number of Attributes: "<<attributes_count<<std::endl;
        if(attributes_count > 0){
            attributes_info = new Attribute_info[attributes_count];
            for(int i = 0; i<attributes_count; i++){
                attributes_info[i].LoadFromStream(istr);
            }
        }        
        if(attributes_count > 0){
            for(int i = 0; i < attributes_count; i++){
                ostr<<"Attribute "<<i<<": {";
                attributes_info[i].OutputDataRaw(ostr, ", ");
                ostr<<"}"<<std::endl;
            }
            ostr<<std::endl;
        }
    }

    void ReadClassHeader(std::istream& istr, std::ostream& err) {
        header = GetNextU32(istr);
        if(header != 0xCAFEBABE){
            err<<"ERROR: .class File Begins With \""<<std::hex<<header<<std::dec<<"\" instead of \"0xCAFEBABE\""<<std::endl;
        }
    }

    void OutputDataRaw(std::ostream& ostr = std::cout) {
        ostr<<".class version: "<<major_version<<"."<<minor_version<<std::endl;
        
        ostr<<"Constant Pool:"<<std::endl;
        constant_pool->OutputMembersRaw(ostr, "\n\t");

        ostr<<std::endl<<"Class Access Flags: {";
        AccessFlags::OutputClassAccessFlags(ostr, access_flags, " | ");
        ostr<<"}"<<std::endl;

        ostr<<"This Class Index: "<<this_class_index<<std::endl;
        ostr<<"Super Class Index: "<<this_class_index<<std::endl;

        ostr<<"Number of Interfaces: "<<interfaces_count<<std::endl;
        if(interfaces_count > 0){
            ostr<<"Interface Indices: {"<<interface_indices[0];
            for(int i = 1; i < interfaces_count; i++){
                ostr<<", "<<interface_indices[i];
            }
            ostr<<std::endl;
        }

        ostr<<"Number of Fields: "<<fields_count;
        if(fields_count > 0){
            for(int i = 0; i < fields_count; i++){
                ostr<<std::endl<<"Field "<<i<<": ";
                fields_info[i].OutputDataRaw(ostr, "\n\t");
            }
        }
        ostr<<std::endl<<std::endl;

        ostr<<"Number of Methods: "<<methods_count;
        if(methods_count > 0){
            for(int i = 0; i < methods_count; i++){
                ostr<<std::endl<<"Method "<<i<<": ";
                methods_info[i].OutputDataRaw(ostr, "\n\t");
            }
        }
        ostr<<std::endl<<std::endl;

        ostr<<"Number of Attributes: "<<attributes_count<<std::endl;
        if(attributes_count > 0){
            for(int i = 0; i < attributes_count; i++){
                ostr<<"Attribute "<<i<<": {";
                attributes_info[i].OutputDataRaw(ostr, ", ");
                ostr<<"}"<<std::endl;
            }
            ostr<<std::endl;
        }
    }

    ConstantPool* GetConstantPool(){return constant_pool;}
};

int main(int argc, char** argv) {
    if(argc == 1){std::cerr<<"ERROR: No Argument Was Passed!"<<std::endl; return 1;}
    std::ifstream istr(argv[1], std::ios::binary);

    ClassFile classfile;
    classfile.SynchronousLoadOutputRaw(istr);

    return 0;
}