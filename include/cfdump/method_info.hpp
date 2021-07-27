#ifndef CFDUMP_METHOD_INFO_HPP
#define CFDUMP_METHOD_INFO_HPP

#include<stdint.h>
#include<iostream>
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include "cfdump/methodaccessflags.hpp"

namespace cfd {

class Attribute_info;

class Method_info : public iou::IBinaryReadable, public iou::IJSONWriteable {    
    MethodAccessFlags access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    Attribute_info* attributes;

public:
    Method_info();
    Method_info(std::istream& istr, std::ostream& err = std::cerr);
    ~Method_info();

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif