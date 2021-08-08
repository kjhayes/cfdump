#ifndef CFDUMP_METHODACCESSFLAGS_HPP
#define CFDUMP_METHODACCESSFLAGS_HPP

#include<iostream>
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ibinarywriteable.hpp"
#include "iostream-util/ijsonwriteable.hpp"

namespace cfd {

class MethodAccessFlags : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable{
public:
    uint16_t flags;

    enum Enum{
        M_PUBLIC = 0x0001,
        M_PRIVATE = 0x0002,
        M_PROTECTED = 0x0004,
        M_STATIC = 0x0008,
        M_FINAL = 0x0010,
        M_SYNCHRONIZED = 0x0020,
        M_BRIDGE = 0x0040,
        M_VARARGS = 0x0080,
        M_NATIVE = 0x0100,
        M_ABSTRACT = 0x0400,
        M_STRICT = 0x0800,
        M_SYNTHETIC = 0x1000
    };
    static const char* MethodAccessStrings[12];
    
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, const iou::JSONFormatting formatting) const override;
};

}

#endif