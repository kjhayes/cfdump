#include<cstdlib>
#include<assert.h>
#include<fstream>
#include<iostream>
#include<stdint.h>
#include<cstring>
#include<limits>

static_assert(std::numeric_limits<float>::is_iec559);
static_assert(std::numeric_limits<double>::is_iec559);

//Read Byte Functions
uint8_t GetNextU8(std::istream& istr){
    return istr.get();
}
//Big Endian, Like .class Format
uint16_t GetNextU16(std::istream& istr){
    uint16_t u = ((uint16_t)GetNextU8(istr)) << 8;
    u |= (uint16_t)GetNextU8(istr);
    return u;   
}
uint32_t GetNextU32(std::istream& istr){
    uint32_t u = ((uint32_t)GetNextU16(istr)) << 16;
    u |= (uint32_t)GetNextU16(istr);
    return u;
}
uint64_t GetNextU64(std::istream& istr){
    uint64_t u = ((uint64_t)GetNextU32(istr)) << 32;
    u |= (uint64_t)GetNextU32(istr);    
    return u;
}

class ConstantPoolMember {
public:
    //At Tag Byte
    static ConstantPoolMember* GetConstantPoolMember(std::istream& istr);
    
    //Past Tag Byte
    virtual void LoadFromStream(std::istream& istr) = 0;
    virtual int GetIndex() const = 0;
    virtual const char* GetTag() const = 0; 

    virtual void OutputFormatted(std::ostream&, const char* prefix = "") = 0;    
};
class Utf8_info : public ConstantPoolMember {
public:
    const int index = 1;
    const char* tag = "Utf8_info";
    int GetIndex() const override {return index;}
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

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
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
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    Integer_info(std::istream& istr){LoadFromStream(istr);}

    int32_t value;
    void LoadFromStream(std::istream& istr) override {
        static_assert(sizeof(int32_t) <= sizeof(uint32_t));
        uint32_t i = GetNextU32(istr);
        memcpy(&value, &i, sizeof(int32_t));
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Value: "<<value;
    }
};
class Float_info : public ConstantPoolMember {
public:
    const int index = 4;
    const char* tag = "Float_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    Float_info(std::istream& istr){LoadFromStream(istr);}
    
    float value;
    void LoadFromStream(std::istream& istr) override {
        static_assert(sizeof(float) <= sizeof(uint32_t));
        uint32_t i = GetNextU32(istr);
        memcpy(&i, &value, sizeof(float));
    }
    
    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Value: "<<value;
    }
};
class Long_info : public ConstantPoolMember {
public:
    const int index = 5;
    const char* tag = "Long_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    Long_info(std::istream& istr){LoadFromStream(istr);}
    
    int64_t value;
    void LoadFromStream(std::istream& istr) override {
        static_assert(sizeof(int64_t) <= sizeof(uint64_t));
        uint64_t i = GetNextU64(istr);
        memcpy(&value, &i, sizeof(int64_t));
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Value: "<<value;
    }
};
class Double_info : public ConstantPoolMember {
public:
    const int index = 6;
    const char* tag = "Double_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    Double_info(std::istream& istr){LoadFromStream(istr);}
    
    double value;
    void LoadFromStream(std::istream& istr) override {
        uint64_t i = GetNextU64(istr);
        static_assert(sizeof(double) <= sizeof(uint64_t));
        memcpy(&value, &i, sizeof(double));
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Value: "<<value;
    }
};
class Class_info : public ConstantPoolMember {
public:
    const int index = 7;
    const char* tag = "Class_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    Class_info(std::istream& istr){LoadFromStream(istr);}

    uint16_t name_index;
    void LoadFromStream(std::istream& istr) override {
        name_index = GetNextU16(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Name Index: "<<name_index;
    }
};
class String_info : public ConstantPoolMember {
public:
    const int index = 8;
    const char* tag = "Double_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    String_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t string_index;
    void LoadFromStream(std::istream& istr) override {
        string_index = GetNextU16(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"String Index: "<<string_index;
    }
};
class Fieldref_info : public ConstantPoolMember {
public:
    const int index = 9;
    const char* tag = "Fieldref_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    Fieldref_info(std::istream& istr){LoadFromStream(istr);}

    uint16_t class_index;
    uint16_t nameandtype_index;
    void LoadFromStream(std::istream& istr) override {
        class_index = GetNextU16(istr);
        nameandtype_index = GetNextU16(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Class Index: "<<class_index;
        ostr<<prefix<<"NameAndType Index: "<<nameandtype_index;
    }
};
class Methodref_info : public ConstantPoolMember {
public:
    const int index = 10;
    const char* tag = "Methodref_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    Methodref_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t class_index;
    uint16_t nameandtype_index;
    void LoadFromStream(std::istream& istr) override {
        class_index = GetNextU16(istr);
        nameandtype_index = GetNextU16(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Class Index: "<<class_index;
        ostr<<prefix<<"NameAndType Index: "<<nameandtype_index;
    }
};
class InterfaceMethodref_info : public ConstantPoolMember {
public:
    const int index = 11;
    const char* tag = "InterfaceMethodref_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    InterfaceMethodref_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t class_index;
    uint16_t nameandtype_index;
    void LoadFromStream(std::istream& istr) override {
        class_index = GetNextU16(istr);
        nameandtype_index = GetNextU16(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Class Index: "<<class_index;
        ostr<<prefix<<"NameAndType Index: "<<nameandtype_index;
    }
};
class NameAndType_info : public ConstantPoolMember {
public:
    const int index = 12;
    const char* tag = "NameAndType_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    NameAndType_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t name_index;
    uint16_t descriptor_index;
    void LoadFromStream(std::istream& istr) override {
        name_index = GetNextU16(istr);
        descriptor_index = GetNextU16(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Name Index: "<<name_index;
        ostr<<prefix<<"Descriptor Index: "<<descriptor_index;
    }
};
class MethodHandle_info : public ConstantPoolMember {
public:
    const int index = 15;
    const char* tag = "MethodHandle_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    MethodHandle_info(std::istream& istr){LoadFromStream(istr);}
    
    uint8_t reference_kind;
    uint16_t reference_index;
    void LoadFromStream(std::istream& istr) override {
        reference_kind = GetNextU8(istr);
        reference_index = GetNextU16(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Reference Kind: "<<(unsigned int)reference_kind;
        ostr<<prefix<<"Reference Index: "<<reference_index;
    }
};
class MethodType_info : public ConstantPoolMember {
public:
    const int index = 16;
    const char* tag = "MethodType_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    MethodType_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t descriptor_index;
    void LoadFromStream(std::istream& istr) override {
        descriptor_index = GetNextU16(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Descriptor Index: "<<descriptor_index;
    }
};
class InvokeDynamic_info : public ConstantPoolMember {
public:
    const int index = 18;
    const char* tag = "InvokeDynamic_info";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    InvokeDynamic_info(std::istream& istr){LoadFromStream(istr);}
    
    uint16_t bootstrap_method_attr_index;
    uint16_t nameandtype_index;
    void LoadFromStream(std::istream& istr) override {
        bootstrap_method_attr_index = GetNextU16(istr);
        nameandtype_index = GetNextU16(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Bootstrap Method Attr Index: "<<bootstrap_method_attr_index;
        ostr<<prefix<<"NameAndType Index: "<<nameandtype_index;
    }
};

class CPMError : public ConstantPoolMember {
public:
    const int index = 0;
    const char* tag = "Undefined";
    int GetIndex() const override {return index;}
    const char* GetTag() const override {return tag;}
    CPMError(std::istream& istr){LoadFromStream(istr);}
    
    uint8_t error_index;
    void LoadFromStream(std::istream& istr) override {
        istr.unget();
        error_index = GetNextU8(istr);
    }

    void OutputFormatted(std::ostream& ostr, const char* prefix = "") override {
        ostr<<prefix<<"Error: Index \""<<(unsigned int)error_index<<"\n is Undefined!";
    }
};


ConstantPoolMember* ConstantPoolMember::GetConstantPoolMember(std::istream& istr) {
    switch(GetNextU8(istr)) {
        case 1: {return new Utf8_info(istr);}
        case 3: {return new Integer_info(istr);}
        case 4: {return new Float_info(istr);}
        case 5: {return new Long_info(istr);}
        case 6: {return new Double_info(istr);}
        case 7: {return new Class_info(istr);}
        case 8: {return new String_info(istr);}
        case 9: {return new Fieldref_info(istr);}
        case 10: {return new Methodref_info(istr);}
        case 11: {return new InterfaceMethodref_info(istr);}
        case 12: {return new NameAndType_info(istr);}
        case 15: {return new MethodHandle_info(istr);}
        case 16: {return new MethodType_info(istr);}
        case 18: {return new InvokeDynamic_info(istr);}
        default: {return new CPMError(istr);}
    }
} 

class ConstantPool {
private:
    int count;
    int number_of_members;
    ConstantPoolMember** members;
public:
    ConstantPool(std::istream& istr){
        count = GetNextU16(istr);
        number_of_members = count-1;
        members = new ConstantPoolMember*[count-1];
        for(int i = 0; i < count-1; i++){
            members[i] = ConstantPoolMember::GetConstantPoolMember(istr);
        }
    }
    ~ConstantPool() {
        if(members != nullptr){
            for(int i = 0; i<number_of_members; i++){
                if(members[i] != nullptr) {delete members[i];}
            }
            delete members;
        }
    }

    ConstantPoolMember* GetMember(const int& index) {return members[index];}
    int GetCount() {return count;}
    int GetNumberOfMembers() {return number_of_members;}
};

class Attribute {
public:
    Attribute(){}
    Attribute(std::istream& istr){LoadFromStream(istr);}
    ~Attribute() {if(info != nullptr) {delete info;}}
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t* info = nullptr;

    void LoadFromStream(std::istream& istr){
        attribute_name_index = GetNextU16(istr);
        attribute_length = GetNextU32(istr);
        info = new uint8_t[attribute_length];
        for(int i = 0; i<attribute_length; i++){
            info[i] = GetNextU8(istr);
        }
    }
};

class AccessFlags {
public:
enum FieldAccessFlagsEnum{
        ACC_PUBLIC = 0x0001,
        ACC_PRIVATE = 0x0002,
        ACC_PROTECTED = 0x0004,
        ACC_STATIC = 0x0008,
        ACC_FINAL = 0x0010,
        ACC_VOLATILE = 0x0020,
        ACC_TRANSIENT = 0x0040,
        ACC_SYNTHETIC = 0x1000,
        ACC_ENUM = 0x4000
    };
    const char* FieldAccessStrings[9] = {
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
    void OutputFieldAccessFlags(std::ostream& ostr, const uint16_t& flags, const char* padding = " "){
        bool has_been_output;
        switch(flags){
            case FieldAccessFlagsEnum::ACC_ENUM: {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[8];has_been_output = true;}
            case FieldAccessFlagsEnum::ACC_FINAL: {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[4];has_been_output = true;}
            case FieldAccessFlagsEnum::ACC_PRIVATE: {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[1];has_been_output = true;}
            case FieldAccessFlagsEnum::ACC_PROTECTED: {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[2];has_been_output = true;}
            case FieldAccessFlagsEnum::ACC_PUBLIC: {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[0];has_been_output = true;}
            case FieldAccessFlagsEnum::ACC_STATIC: {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[3];has_been_output = true;}
            case FieldAccessFlagsEnum::ACC_SYNTHETIC: {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[7];has_been_output = true;}
            case FieldAccessFlagsEnum::ACC_TRANSIENT: {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[6];has_been_output = true;}
            case FieldAccessFlagsEnum::ACC_VOLATILE: {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[5];has_been_output = true;}
        }
    }
    enum MethodAccessFlagsEnum{
        ACC_PUBLIC = 0x0001,
        ACC_PRIVATE = 0x0002,
        ACC_PROTECTED = 0x0004,
        ACC_STATIC = 0x0008,
        ACC_FINAL = 0x0010,
        ACC_SYNCHRONIZED = 0x0020,
        ACC_BRIDGE = 0x0040,
        ACC_VARARGS = 0x0080,
        ACC_NATIVE = 0x0100,
        ACC_ABSTRACT = 0x0400,
        ACC_STRICT = 0x0800,
        ACC_SYNTHETIC = 0x1000
    };
    const char* MethodAccessStrings[12] = {
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
    void OutputMethodAccessFlags(std::ostream& ostr, const uint16_t& flags, const char* padding = " "){
        bool has_been_output;
        switch(flags){
            case MethodAccessFlagsEnum::ACC_ABSTRACT: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[9];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_BRIDGE: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[6];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_FINAL: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[4];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_NATIVE: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[8];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_PRIVATE: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[1];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_PROTECTED: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[2];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_PUBLIC: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[0];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_STATIC: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[3];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_STRICT: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[10];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_SYNCHRONIZED: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[5];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_SYNTHETIC: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[11];has_been_output = true;}
            case MethodAccessFlagsEnum::ACC_VARARGS: {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[7];has_been_output = true;}
        }
    }
    enum ClassAccessFlagsEnum {
        ACC_PUBLIC = 0x0001,
        ACC_FINAL = 0x0010,
        ACC_SUPER = 0x0020,
        ACC_INTERFACE = 0x0200,
        ACC_ABSTRACT = 0x0400,
        ACC_SYNTHETIC = 0x1000,
        ACC_ANNOTATION = 0x2000,
        ACC_ENUM = 0x4000
    };
    const char* ClassAccessStrings[8] = {
        "PUBLIC",       //0
        "FINAL",        //1
        "SUPER",        //2
        "INTERFACE",    //3
        "ABSTRACT",     //4
        "SYNTHETIC",    //5
        "ANNOTATION",   //6
        "ENUM"          //7
    };
    void OutputClassAccessFlags(std::ostream& ostr, const uint16_t& flags, const char* padding = " ") {
        bool has_been_output;
        switch(flags){
            case ClassAccessFlagsEnum::ACC_ABSTRACT: {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[4];has_been_output = true;}
            case ClassAccessFlagsEnum::ACC_ANNOTATION: {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[6];has_been_output = true;}
            case ClassAccessFlagsEnum::ACC_ENUM: {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[7];has_been_output = true;}
            case ClassAccessFlagsEnum::ACC_FINAL: {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[1];has_been_output = true;}
            case ClassAccessFlagsEnum::ACC_INTERFACE: {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[3];has_been_output = true;}
            case ClassAccessFlagsEnum::ACC_PUBLIC: {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[0];has_been_output = true;}
            case ClassAccessFlagsEnum::ACC_SUPER: {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[2];has_been_output = true;}    
            case ClassAccessFlagsEnum::ACC_SYNTHETIC: {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[5];has_been_output = true;}
        }
    }
};

class Field_info {
    
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    Attribute* attributes;

public:
    Field_info(){}
    Field_info(std::istream& istr){LoadFromStream(istr);}
    ~Field_info() {
        if(attributes != nullptr){
            delete attributes;
        }
    }

    void LoadFromStream(std::istream& istr){
        access_flags = GetNextU16(istr);
        name_index = GetNextU16(istr);
        descriptor_index = GetNextU16(istr);
        attributes_count = GetNextU16(istr);
        if(attributes_count > 0){
            attributes = new Attribute[attributes_count];
            for(int i = 0; i<attributes_count; i++){
                attributes[i].LoadFromStream(istr);
            }
        }

    }
};
class Method_info {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    Attribute** attributes;

public:
    Method_info(){}
    Method_info(std::istream& istr){LoadFromStream(istr);}
    ~Method_info() {
        if(attributes != nullptr){
            for(int i = 0; i<attributes_count; i++){
                if(attributes[i] != nullptr) {delete attributes[i];}
            }
            delete attributes;
        }
    }

    void LoadFromStream(std::istream& istr){
        access_flags = GetNextU16(istr);
        name_index = GetNextU16(istr);
        descriptor_index = GetNextU16(istr);
        attributes_count = GetNextU16(istr);
        if(attributes_count > 0){
            attributes = new Attribute*[attributes_count];
            for(int i = 0; i<attributes_count; i++){
                attributes[i] = new Attribute(istr);
            }
        }

    }
};

class ClassFile {
public:
    uint32_t header;
    uint16_t minor_version, major_version;

    ConstantPool* constant_pool;

    uint16_t access_flags;

    uint16_t this_class_index;
    uint16_t super_class_index;

    uint16_t interfaces_count;
    uint16_t* interface_indices = nullptr;

    uint16_t fields_count;
    Field_info* fields = nullptr;

    uint16_t methods_count;
    Method_info* methods = nullptr;

    uint16_t attribute_count;
    Attribute* attributes = nullptr;

    ClassFile(std::istream& istr, std::ostream& out = std::cout, std::ostream& err = std::cerr){
        ReadClassHeader(istr, err);

        minor_version = GetNextU16(istr);
        major_version = GetNextU16(istr);
        
        constant_pool = new ConstantPool(istr);

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
            fields = new Field_info[fields_count];
            for(int i = 0; i<fields_count; i++){
                fields[i].LoadFromStream(istr);
            }
        }
        
        methods_count = GetNextU16(istr);
        if(methods_count > 0){
            methods = new Method_info[methods_count];
            for(int i = 0; i<methods_count; i++){
                methods[i].LoadFromStream(istr);
            }
        }

        attribute_count = GetNextU16(istr);
        if(attribute_count > 0){
            attributes = new Attribute[attribute_count];
            for(int i = 0; i<attribute_count; i++){
                attributes[i].LoadFromStream(istr);
            }
        }
    }

    ~ClassFile(){
        if(constant_pool != nullptr){delete constant_pool;}
        if(interface_indices != nullptr){delete interface_indices;}
        if(fields != nullptr){delete fields;}
        if(methods != nullptr){delete methods;}
        if(attributes != nullptr){delete attributes;}
    }

    void ReadClassHeader(std::istream& istr, std::ostream& err) {
        header = GetNextU32(istr);
        if(header != 0xCAFEBABE){
            err<<"ERROR: .class File Begins With \""<<std::hex<<header<<std::dec<<"\" instead of \"0xCAFEBABE\""<<std::endl;
        }
    }
};

int main(int argc, char** argv) {

    std::ostream& out = std::cout;
    std::ostream& err = std::cerr;

    if(argc == 1){err<<"ERROR: No Argument Was Passed!"<<std::endl; return 1;}
    std::ifstream istr(argv[1], std::ios::binary);

    ClassFile classfile(istr);   
 
    return 0;
}