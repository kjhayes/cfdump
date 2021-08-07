#ifndef CFDUMP_CLASSFILE_INFO_HPP
#define CFDUMP_CLASSFILE_INFO_HPP

#include<iostream>
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include "cfdump/classaccessflags.hpp"

namespace cfd {

class ConstantPool;
class Field_info;
class Method_info;
class Attribute_info;

class ClassFile_info : public iou::IBinaryReadable, public iou::IJSONWriteable {
public:
    uint32_t header;
    uint16_t minor_version, major_version;

    ConstantPool* constant_pool;

    ClassAccessFlags access_flags;

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

    ClassFile_info();
    ClassFile_info(std::istream& istr, std::ostream& err = std::cerr);
    ~ClassFile_info();

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif