#ifndef CFDUMP_CONSTANTPOOL_HPP
#define CFDUMP_CONSTANTPOOL_HPP

#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"

namespace cfd {

class ConstantPoolMember;

class ConstantPool : public iou::IBinaryReadable, public iou::IJSONWriteable {
private:
    int count;
    int number_of_members;
    ConstantPoolMember** members;
public:
    ConstantPool(std::istream& istr, std::ostream& err = std::cerr);
    ~ConstantPool();

    ConstantPoolMember* GetMember_PoolIndex(const int& index);
    ConstantPoolMember* GetMember_ArrayIndex(const int& index);
    
    int GetCount();
    int GetNumberOfMembers();

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif