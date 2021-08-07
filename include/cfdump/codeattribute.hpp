#ifndef CFDUMP_CODEATTRIBUTE_HPP
#define CFDUMP_CODEATTRIBUTE_HPP

#include<iostream>
#include<list>
#include "cfdump/jvmis.hpp"
#include "cfdump/attribute_info.hpp"
#include "iostream-util/ijsonwriteable.hpp"

namespace cfd {

class CodeAttribute : iou::IJSONWriteable {
public:
    std::list<jvmis::Instruction*> instructions;

    CodeAttribute(const Attribute_info& attr, std::ostream& err = std::cerr);
    ~CodeAttribute();

    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

}

#endif