#ifndef CFDUMP_ATTRIBUTE_INFO_HPP
#define CFDUMP_ATTRIBUTE_INFO_HPP

#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include<stdint.h>

namespace cfd {

class Attribute_info : public iou::IBinaryReadable, public iou::IJSONWriteable {
public:
    Attribute_info();
    Attribute_info(std::istream& istr, std::ostream& err = std::cerr);
    ~Attribute_info();
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t* info = nullptr;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif