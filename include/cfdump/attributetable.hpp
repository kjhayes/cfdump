#ifndef CFDUMP_ATTRIBUTETABLE_HPP
#define CFDUMP_ATTRIBUTETABLE_HPP

#include<stdint.h>
#include "iostream-util/ijsonwriteable.hpp"
#include "iostream-util/ibinaryreadable.hpp"
#include<list>

namespace cfd {

class Attribute_info;

class AttributeTable : public iou::IBinaryReadable, public iou::IJSONWriteable {
public:
    //uint16_t attributes_count;
    std::list<Attribute_info*> attributes_info;

    ~AttributeTable();
    
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif