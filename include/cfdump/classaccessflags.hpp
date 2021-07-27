#ifndef CFDUMP_CLASSACCESSFLAGS_HPP
#define CFDUMP_CLASSACCESSFLAGS_HPP

#include<iostream>
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"

namespace cfd {

class ClassAccessFlags : public iou::IBinaryReadable, public iou::IJSONWriteable {
public:
    uint16_t flags;

    enum Enum {
        C_PUBLIC = 0x0001,
        C_FINAL = 0x0010,
        C_SUPER = 0x0020,
        C_INTERFACE = 0x0200,
        C_ABSTRACT = 0x0400,
        C_SYNTHETIC = 0x1000,
        C_ANNOTATION = 0x2000,
        C_ENUM = 0x4000,
        C_MODULE = 0x8000
    };
    static const char* ClassAccessStrings[9];

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, const iou::JSONFormatting formatting) const override;
};

}

#endif