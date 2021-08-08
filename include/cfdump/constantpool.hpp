#ifndef CFDUMP_CONSTANTPOOL_HPP
#define CFDUMP_CONSTANTPOOL_HPP

#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include "iostream-util/ibinarywriteable.hpp"

#include<list>

namespace cfd {

class ConstantPoolMember;

class ConstantPool : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable {
private:
    std::list<ConstantPoolMember*> members;
public:
    ConstantPool(std::istream& istr, std::ostream& err = std::cerr);
    ~ConstantPool();

    uint16_t GetNumberOfEntries() const;
    uint16_t GetCount() const;

    uint16_t GetIndexOfMember(ConstantPoolMember* member) const;
    ConstantPoolMember* GetMemberAtIndex(const uint16_t& index) const;

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif