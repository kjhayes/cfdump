#ifndef CFDUMP_EXCEPTIONTABLEMEMBER_HPP
#define CFDUMP_EXCEPTIONTABLEMEMBER_HPP

#include "iostream-util/ijsonwriteable.hpp"
#include "iostream-util/ibinaryreadable.hpp"
#include<stdint.h>

namespace cfd {

struct ExceptionTableMember : public iou::IJSONWriteable, public iou::IBinaryReadable {
public:
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catchtype;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif