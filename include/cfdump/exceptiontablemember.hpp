#ifndef CFDUMP_EXCEPTIONTABLEMEMBER_HPP
#define CFDUMP_EXCEPTIONTABLEMEMBER_HPP

#include "iostream-util/ijsonwriteable.hpp"
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ibinarywriteable.hpp"
#include "cfdump/constantpoolmember.hpp"
#include<stdint.h>

namespace cfd {

struct ExceptionTableMember : public iou::IJSONWriteable, public iou::IBinaryReadable, public iou::IBinaryWriteable {
public:
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    ConstantPoolReference catchtype;

    void ResolveIndexReferences(ConstantPool* pool);

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif