#include "cfdump/attribute_info.hpp"

#include "cfdump/jvmis.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/streamwrite.hpp"
#include "cfdump/jvmis.hpp"
#include<string>

namespace cfd {

CodeAttribute::~CodeAttribute() {
    for(auto iter = instructions.begin(); iter != instructions.end(); iter++){
        if((*iter) != nullptr){
            delete (*iter);
        }
    }
}

size_t CodeAttribute::GetLengthWithoutHeader() const {    
    size_t code_length = jvmis::Instruction::GetCodeLength(instructions);
    size_t exceptions_length = exceptiontable.size() * 8;
    return (8 + code_length + 2 + exceptions_length + attribute_table.Length());
}

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
void CodeAttribute::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutBEU16(ostr, AttributeNameIndexTable::last_set_table->Code);
    
    iou::PutBEU32(ostr, GetLengthWithoutHeader());

    iou::PutBEU16(ostr, max_stack);
    iou::PutBEU16(ostr, max_locals);
    
    size_t code_length = jvmis::Instruction::GetCodeLength(instructions);
    if(code_length>0xFFFFFFFF){std::cerr<<"ERROR: ByteCode Inside Code Attribute Is Too Long To Write"<<std::endl;}
    iou::PutBEU32(ostr, code_length);
    for(auto iter = instructions.begin(); iter != instructions.end(); iter++){
        (*iter)->WriteToBinaryStream(ostr);
    }
    size_t exceptions_length = exceptiontable.size() * 8;
    if(exceptions_length>0xFFFF){std::cerr<<"ERROR: Too Many Exceptions In Code Attribute To Write"<<std::endl;}
    iou::PutBEU16(ostr, exceptions_length);
    for(auto iter = exceptiontable.begin(); iter != exceptiontable.end(); iter++){
        (*iter).WriteToBinaryStream(ostr);
    }
    attribute_table.WriteToBinaryStream(ostr);
}
void CodeAttribute::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Attribute Name", "Code", formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", attribute_name_index.Index(), formatting);
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