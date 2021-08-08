#ifndef CFDUMP_METHOD_INFO_HPP
#define CFDUMP_METHOD_INFO_HPP

#include<stdint.h>
#include<iostream>
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ibinarywriteable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include "cfdump/methodaccessflags.hpp"
#include "cfdump/attributetable.hpp"
#include "cfdump/constantpoolmember.hpp"

namespace cfd {

class Attribute_info;
class AttributeNameIndexTable;

class Method_info : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable {    
public:
    MethodAccessFlags access_flags;
    ConstantPoolReference name_index;
    ConstantPoolReference descriptor_index;
    AttributeTable attribute_table;

    Method_info();
    Method_info(std::istream& istr, std::ostream& err = std::cerr);

    void ResolveIndexReferences(ConstantPool* pool);

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif