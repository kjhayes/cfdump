#ifndef CFDUMP_ATTRIBUTETABLE_HPP
#define CFDUMP_ATTRIBUTETABLE_HPP

#include<stdint.h>
#include "iostream-util/ijsonwriteable.hpp"
#include "iostream-util/ibinarywriteable.hpp"
#include "iostream-util/ibinaryreadable.hpp"
#include<vector>

namespace cfd {

class Attribute_info;
class ConstantPool;

class AttributeTable : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable {
public:
    //uint16_t attributes_count;
    std::vector<Attribute_info*> attributes_info;

    ~AttributeTable();
    
    size_t Length() const;

    void ResolveIndexReferences(ConstantPool* pool);

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif