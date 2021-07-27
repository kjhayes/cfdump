#ifndef CFDUMP_FIELD_INFO_HPP
#define CFDUMP_FIELD_INFO_HPP

#include<stdint.h>
#include<iostream>
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include "cfdump/fieldaccessflags.hpp"

namespace cfd {

class Attribute_info;

class Field_info : public iou::IBinaryReadable, public iou::IJSONWriteable {    
    FieldAccessFlags access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    Attribute_info* attributes;

public:
    Field_info();
    Field_info(std::istream& istr, std::ostream& err = std::cerr);
    ~Field_info();

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif