#include "cfdump/codeattribute.hpp"

#include<sstream>

#include "iostream-util/streamread.hpp"

namespace cfd {

CodeAttribute::CodeAttribute(const Attribute_info& attr, std::ostream& err) {
    std::stringstream sstr(std::string(reinterpret_cast<char*>(attr.info), attr.attribute_length));
    while(!sstr.eof()){
        uint8_t opcode = iou::GetNextU8(sstr, err);
        jvmis::Instruction* ins = jvmis::Instruction::NewInstructionOfOpcode((jvmis::OPCODE)opcode);
        ins->ReadFromBinaryStream(sstr, err);
        instructions.push_back(ins);
    }
}
CodeAttribute::~CodeAttribute() {
    for(auto iter = instructions.begin(); iter != instructions.end(); iter++){
        if((*iter) != nullptr){
            delete (*iter);
        }
    }
}

void CodeAttribute::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    if(instructions.size()>0){
    int i = 0;
    for(auto iter = instructions.begin(); iter == instructions.end(); iter++){
        iou::JSON::WriteJSONObject(ostr, (std::to_string(i)).c_str(), *(*iter), formatting, i == (instructions.size()-1));
        i++;
    }
    }
}

}