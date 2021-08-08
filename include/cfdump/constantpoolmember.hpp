#ifndef CFDUMP_CONSTANTPOOLMEMBER_HPP
#define CFDUMP_CONSTANTPOOLMEMBER_HPP

#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include "iostream-util/ibinarywriteable.hpp"
#include<string>

namespace cfd {

typedef std::string MUTF8String;

class ConstantPool;
class ConstantPoolMember;

class ConstantPoolReference {
public:
    ConstantPoolMember* ptr = nullptr;
    ConstantPool* pool = nullptr;
    uint16_t read_index = 0;

    void ResolveRead(ConstantPool* pool);
    uint16_t Index() const;
};

class ConstantPoolMember : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable {
public:
    virtual int GetIndexOfTag() const = 0;    
    virtual int NumberOfCPEntriesTaken() const {return 1;}

    virtual void ResolveIndexReferences(ConstantPool* pool);

    static ConstantPoolMember* NewConstantPoolMember(std::istream& istr, std::ostream& err = std::cerr);
    static const char* GetConstantPoolMemberString(const ConstantPoolMember& cpm);
};

class Utf8_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    
    Utf8_info(std::istream& istr, std::ostream& err = std::cerr);

    //uint16_t length;
    //uint8_t* data;
    MUTF8String string;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Integer_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Integer_info(std::istream& istr, std::ostream& err = std::cerr);

    int32_t value;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Float_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Float_info(std::istream& istr, std::ostream& err = std::cerr);
    
    float value;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Long_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Long_info(std::istream& istr, std::ostream& err = std::cerr);
    
    int64_t value;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
    int NumberOfCPEntriesTaken() const override;
};
class Double_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Double_info(std::istream& istr, std::ostream& err = std::cerr);
    
    double value;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
    int NumberOfCPEntriesTaken() const override;
};
class Class_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Class_info(std::istream& istr, std::ostream& err = std::cerr);

    ConstantPoolReference name_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class String_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    String_info(std::istream& istr, std::ostream& err = std::cerr);
    
    ConstantPoolReference string_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Fieldref_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Fieldref_info(std::istream& istr, std::ostream& err = std::cerr);

    ConstantPoolReference class_index;
    ConstantPoolReference nameandtype_index;
    void ResolveIndexReferences(ConstantPool* pool) override;
    
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Methodref_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Methodref_info(std::istream& istr, std::ostream& err = std::cerr);
    
    ConstantPoolReference class_index;
    ConstantPoolReference nameandtype_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class InterfaceMethodref_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    InterfaceMethodref_info(std::istream& istr, std::ostream& err = std::cerr);
    
    ConstantPoolReference class_index;
    ConstantPoolReference nameandtype_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class NameAndType_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    NameAndType_info(std::istream& istr, std::ostream& err = std::cerr);
    
    ConstantPoolReference name_index;
    ConstantPoolReference descriptor_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class MethodHandle_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    MethodHandle_info(std::istream& istr, std::ostream& err = std::cerr);
    
    uint8_t reference_kind;
    ConstantPoolReference reference_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class MethodType_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    MethodType_info(std::istream& istr, std::ostream& err = std::cerr);
    
    ConstantPoolReference descriptor_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Dynamic_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Dynamic_info(std::istream& istr, std::ostream& err = std::cerr);
    
    ConstantPoolReference bootstrap_method_attr_index;
    ConstantPoolReference nameandtype_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class InvokeDynamic_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    InvokeDynamic_info(std::istream& istr, std::ostream& err = std::cerr);
    
    ConstantPoolReference bootstrap_method_attr_index;
    ConstantPoolReference nameandtype_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Module_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Module_info(std::istream& istr, std::ostream& err = std::cerr);
    
    ConstantPoolReference name_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Package_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Package_info(std::istream& istr, std::ostream& err = std::cerr);
    
    ConstantPoolReference name_index;
    void ResolveIndexReferences(ConstantPool* pool) override;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
/*
class UnusuableConstantPoolMember : public ConstantPoolMember {
    int GetIndexOfTag() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
*/
class CPMError : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    CPMError(std::istream& istr, std::ostream& err = std::cerr);
    
    uint8_t error_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif