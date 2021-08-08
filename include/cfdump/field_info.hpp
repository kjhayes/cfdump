#ifndef CFDUMP_FIELD_INFO_HPP
#define CFDUMP_FIELD_INFO_HPP

#include<stdint.h>
#include<iostream>
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ibinarywriteable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include "cfdump/fieldaccessflags.hpp"
#include "cfdump/constantpoolmember.hpp"
#include "cfdump/attributetable.hpp"

namespace cfd {

class Attribute_info;

class Field_info : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable {    
    FieldAccessFlags access_flags;
    ConstantPoolReference name_index;
    ConstantPoolReference descriptor_index;
    AttributeTable attribute_table;

public:
    Field_info();
    Field_info(std::istream& istr, std::ostream& err = std::cerr);

    void ResolveIndexReferences(ConstantPool* pool);

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif