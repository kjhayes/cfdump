#ifndef CFDUMP_CLASSFILE_INFO_HPP
#define CFDUMP_CLASSFILE_INFO_HPP

#include<iostream>
#include "cfdump/attributetable.hpp"
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include "iostream-util/ibinarywriteable.hpp"
#include "cfdump/classaccessflags.hpp"
#include "cfdump/attributenameindextable.hpp"
#include "cfdump/constantpoolmember.hpp"
#include<list>

namespace cfd {

class Field_info;
class Method_info;
class Attribute_info;

class ClassFile_info : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable {
public:
    uint32_t header;
    uint16_t minor_version, major_version;

    ConstantPool* constant_pool;
    AttributeNameIndexTable attribute_name_index_table;

    ClassAccessFlags access_flags;

    ConstantPoolReference this_class_index;
    ConstantPoolReference super_class_index;

    std::list<ConstantPoolReference> interfaces;

    std::list<Field_info> fields;

    std::list<Method_info> methods;

    AttributeTable attribute_table;

    ClassFile_info();
    ClassFile_info(std::istream& istr, std::ostream& err = std::cerr);
    ~ClassFile_info();

    void ResolveIndexReferences();

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif