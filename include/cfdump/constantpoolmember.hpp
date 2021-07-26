#ifndef CFDUMP_CONSTANTPOOLMEMBER_HPP
#define CFDUMP_CONSTANTPOOLMEMBER_HPP

#include "iostream-util/streamread.hpp"
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include "iostream-util/json.hpp"

class ConstantPoolMember : public iou::IBinaryReadable, public iou::IJSONWriteable {
public:
    size_t byteOffsetFromClassFile;
    
    virtual int GetIndexOfTag() const = 0;    
    virtual int NumberOfCPEntriesTaken() const {return 1;}
    
    static ConstantPoolMember* GetConstantPoolMember(std::istream& istr, const std::streampos& cf_offset, int* number_of_cp_entries_taken);
    static const char* GetConstantPoolMemberString(const ConstantPoolMember& cpm);
};

class Utf8_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    
    Utf8_info(std::istream& istr, std::ostream& err = std::cerr);
    ~Utf8_info();

    uint16_t length;
    uint8_t* data;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Integer_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Integer_info(std::istream& istr);

    int32_t value;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Float_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Float_info(std::istream& istr);
    
    float value;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Long_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Long_info(std::istream& istr);
    
    int64_t value;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
    int NumberOfCPEntriesTaken() const override;
};
class Double_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Double_info(std::istream& istr);
    
    double value;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
    int NumberOfCPEntriesTaken() const override;
};
class Class_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Class_info(std::istream& istr);

    uint16_t name_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class String_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    String_info(std::istream& istr);
    
    uint16_t string_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Fieldref_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Fieldref_info(std::istream& istr);

    uint16_t class_index;
    uint16_t nameandtype_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Methodref_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Methodref_info(std::istream& istr);
    
    uint16_t class_index;
    uint16_t nameandtype_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class InterfaceMethodref_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    InterfaceMethodref_info(std::istream& istr);
    
    uint16_t class_index;
    uint16_t nameandtype_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class NameAndType_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    NameAndType_info(std::istream& istr);
    
    uint16_t name_index;
    uint16_t descriptor_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class MethodHandle_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    MethodHandle_info(std::istream& istr);
    
    uint8_t reference_kind;
    uint16_t reference_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class MethodType_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    MethodType_info(std::istream& istr);
    
    uint16_t descriptor_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Dynamic_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Dynamic_info(std::istream& istr);
    
    uint16_t bootstrap_method_attr_index;
    uint16_t nameandtype_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class InvokeDynamic_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    InvokeDynamic_info(std::istream& istr);
    
    uint16_t bootstrap_method_attr_index;
    uint16_t nameandtype_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Module_info : public ConstantPoolMember {
public:
    ;
    int GetIndexOfTag() const override;
    Module_info(std::istream& istr);
    
    uint16_t name_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class Package_info : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    Package_info(std::istream& istr);
    
    uint16_t name_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

class UnusuableConstantPoolMember : public ConstantPoolMember {
    int GetIndexOfTag() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

class CPMError : public ConstantPoolMember {
public:
    int GetIndexOfTag() const override;
    CPMError(std::istream& istr);
    
    uint8_t error_index;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

#endif