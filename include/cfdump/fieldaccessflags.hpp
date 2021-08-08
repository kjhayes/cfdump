#ifndef CFDUMP_FIELDACCESSFLAGS_HPP
#define CFDUMP_FIELDACCESSFLAGS_HPP

#include<iostream>
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ibinarywriteable.hpp"
#include "iostream-util/ijsonwriteable.hpp"

namespace cfd {

class FieldAccessFlags : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable {
public:
    uint16_t flags;

    enum Enum{
        F_PUBLIC = 0x0001,
        F_PRIVATE = 0x0002,
        F_PROTECTED = 0x0004,
        F_STATIC = 0x0008,
        F_FINAL = 0x0010,
        F_VOLATILE = 0x0020,
        F_TRANSIENT = 0x0040,
        F_SYNTHETIC = 0x1000,
        F_ENUM = 0x4000
    };
    static const char* FieldAccessStrings[9];
    
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, const iou::JSONFormatting formatting) const override;
};

}

#endif