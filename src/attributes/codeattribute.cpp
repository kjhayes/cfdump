#include "cfdump/attribute_info.hpp"

#include "cfdump/jvmis.hpp"
#include "iostream-util/streamread.hpp"
#include "cfdump/jvmis.hpp"
#include<string>

namespace cfd {

void CodeAttribute::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    attribute_length = iou::GetNextBEU32(istr, err);
    max_stack = iou::GetNextBEU16(istr, err);
    max_locals = iou::GetNextBEU16(istr, err);
    uint32_t code_length = iou::GetNextBEU32(istr, err);
    std::streampos info_start = istr.tellg();
    while(istr.tellg() < (info_start+(std::streampos)code_length)){
        uint8_t opcode = iou::GetNextU8(istr, err);
        jvmis::Instruction* ins = jvmis::Instruction::NewInstructionOfOpcode((jvmis::OPCODE)opcode);
        ins->ReadFromBinaryStream(istr, err);
        instructions.push_back(ins);
    }
    uint16_t exceptiontablelength = iou::GetNextBEU16(istr, err);
    for(int i = 0; i < exceptiontablelength; i++) {
        ExceptionTableMember etmem;
        etmem.ReadFromBinaryStream(istr, err);
        exceptiontable.push_back(etmem);
    }
    attribute_table.ReadFromBinaryStream(istr, err);
}
CodeAttribute::~CodeAttribute() {
    for(auto iter = instructions.begin(); iter != instructions.end(); iter++){
        if((*iter) != nullptr){
            delete (*iter);
        }
    }
}

void CodeAttribute::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Attribute Name", "Code", formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", attribute_name_index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Byte Length", attribute_length, formatting, (instructions.size() <= 0));
    iou::JSON::WriteJSONUnsigned(ostr, "Max Stack", max_stack, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Max Locals", max_stack, formatting);
    uint32_t code_length = jvmis::Instruction::GetCodeLength(instructions);
    iou::JSON::WriteJSONUnsigned(ostr, "Code Length", code_length, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Instruction Count", instructions.size(), formatting);
    if(instructions.size() > 0){
        iou::JSON::BeginWriteJSONArray(ostr, "Bytecode", formatting);
        int i = 0;
        for(auto iter = instructions.begin(); iter != instructions.end(); iter++){
            iou::JSON::WriteJSONArrayObject(ostr, *(*iter), formatting, i >= (instructions.size()-1));
            i++;
        }
        iou::JSON::EndWriteJSONArray(ostr, formatting);
    }
    iou::JSON::WriteJSONUnsigned(ostr, "Exception Table Count", exceptiontable.size(), formatting);
    if(exceptiontable.size() > 0) {
        iou::JSON::BeginWriteJSONArray(ostr, "Exception Table", formatting);
        int i = 0;
        for(auto iter = exceptiontable.begin(); iter != exceptiontable.end(); iter++){
            iou::JSON::WriteJSONArrayObject(ostr, (*iter), formatting, (i == (exceptiontable.size() - 1)));
            i++;
        }
        iou::JSON::EndWriteJSONArray(ostr, formatting);
    }
    iou::JSON::WriteJSONObject(ostr, "Attributes", attribute_table, formatting, true);
}

}