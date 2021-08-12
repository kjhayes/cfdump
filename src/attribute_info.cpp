#include "cfdump/attribute_info.hpp"

#include "cfdump/attributenameindextable.hpp"

#include "iostream-util/streamread.hpp"
#include "iostream-util/streamwrite.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

Attribute_info::~Attribute_info() {if(info != nullptr) {delete[] info;}}

size_t Attribute_info::GetLengthWithoutHeader() const {return attribute_length;}

void Attribute_info::ResolveIndexReferences(ConstantPool* pool){
    attribute_name_index.ResolveRead(pool);
}
void Attribute_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    attribute_length = iou::GetNextBEU32(istr, err);
    if(attribute_length > 0){
        info = new uint8_t[attribute_length];
        for(int i = 0; i<attribute_length; i++){
            info[i] = iou::GetNextU8(istr);
        }
    }
}
void Attribute_info::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutBEU16(ostr, attribute_name_index.Index());
    iou::PutBEU32(ostr, attribute_length);
    for(int i = 0; i<attribute_length; i++){
        iou::PutU8(ostr, info[i]);
    }
}
void Attribute_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Attribute Name", "Unknown", formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", attribute_name_index.Index(), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Byte Length", attribute_length, formatting, (info==nullptr));
    if(info != nullptr){
        iou::JSON::BeginWriteJSONArray(ostr, "Data", formatting);
        for(int i = 0; i < attribute_length; i++){
            iou::JSON::WriteJSONArrayHex(ostr, info[i], formatting, (i == (attribute_length-1)));
        }
        iou::JSON::EndWriteJSONArray(ostr, formatting, true);
    }
}
//Code Attr
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
        exceptiontable.emplace_back();
        exceptiontable.back().ReadFromBinaryStream(istr, err);
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
    iou::JSON::WriteJSONObject(ostr, "Attribute Table", attribute_table, formatting, true);
}
//
Attribute_info* Attribute_info::NewAttributeOfNameIndex(const uint16_t& index, const AttributeNameIndexTable& table) {
    if(index == table.ConstantValue) {return new ConstantValueAttribute();}
    else if(index == table.Code) {return new CodeAttribute();}
    else if(index == table.StackMapTable) {return new StackMapTableAttribute();}
    else if(index == table.Exceptions) {return new ExceptionsAttribute();}
    else if(index == table.InnerClasses) {return new InnerClassesAttribute();}
    else if(index == table.EnclosingMethod) {return new EnclosingMethodAttribute();}
    else if(index == table.Synthetic) {return new SyntheticAttribute();}
    else if(index == table.Signature) {return new SignatureAttribute();}
    else if(index == table.SourceFile) {return new SourceFileAttribute();}
    else if(index == table.SourceDebugExtension) {return new SourceDebugExtensionAttribute();}
    else if(index == table.LineNumberTable) {return new LineNumberTableAttribute();}
    else if(index == table.LocalVariableTable) {return new LocalVariableTableAttribute();}
    else if(index == table.LocalVariableTypeTable) {return new LocalVariableTypeTableAttribute();}
    else if(index == table.Deprecated) {return new DeprecatedAttribute();}
    else if(index == table.RuntimeVisibleAnnotations) {return new RuntimeVisibleAnnotationsAttribute();}
    else if(index == table.RuntimeInvisibleAnnotations) {return new RuntimeInvisibleAnnotationsAttribute();}
    else if(index == table.RuntimeVisibleParameterAnnotations) {return new RuntimeVisibleParameterAnnotationsAttribute();}
    else if(index == table.RuntimeInvisibleParameterAnnotations) {return new RuntimeInvisibleParameterAnnotationsAttribute();}
    else if(index == table.RuntimeVisibleTypeAnnotations) {return new RuntimeVisibleTypeAnnotationsAttribute();}
    else if(index == table.RuntimeInvisibleTypeAnnotations) {return new RuntimeInvisibleTypeAnnotationsAttribute();}
    else if(index == table.AnnotationDefault) {return new AnnotationDefaultAttribute();}
    else if(index == table.BootstrapMethods) {return new BootstrapMethodsAttribute();}
    else if(index == table.MethodParameters) {return new MethodParametersAttribute();}
    else if(index == table.Module) {return new ModuleAttribute();}
    else if(index == table.ModulePackages) {return new ModulePackagesAttribute();}
    else if(index == table.ModuleMainClass) {return new ModuleMainClassAttribute();}
    else if(index == table.NestHost) {return new NestHostAttribute();}
    else if(index == table.NestMembers) {return new NestMembersAttribute();}
    else if(index == table.Record) {return new RecordAttribute();}
    else {
        return new UnknownAttribute();
    }
}

}