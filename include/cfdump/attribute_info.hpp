#ifndef CFDUMP_ATTRIBUTE_INFO_HPP
#define CFDUMP_ATTRIBUTE_INFO_HPP

#include "cfdump/attributetable.hpp"
#include "cfdump/attributenameindextable.hpp"
#include "cfdump/exceptiontablemember.hpp"
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include<stdint.h>

#include<list>
#include "cfdump/jvmis.hpp"

namespace cfd {

class Attribute_info : public iou::IBinaryReadable, public iou::IJSONWriteable {
public:
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t* info;

    ~Attribute_info();

    static Attribute_info* NewAttributeOfNameIndex(const uint16_t& index, const AttributeNameIndexTable& table);

    virtual void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    virtual void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

class ConstantValueAttribute : public Attribute_info {};
class CodeAttribute : public Attribute_info {
public:
    uint16_t max_stack;
    uint16_t max_locals;
    //uint32_t code_length;
    std::list<jvmis::Instruction*> instructions;
    //uint16_t exceptiontablelength;
    std::list<ExceptionTableMember> exceptiontable;
    AttributeTable attribute_table;

    ~CodeAttribute();

    void ReadFromBinaryStream(std::istream& istr, std::ostream& err) override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class StackMapTableAttribute : public Attribute_info {};
class ExceptionsAttribute : public Attribute_info {};
class InnerClassesAttribute : public Attribute_info {};
class EnclosingMethodAttribute : public Attribute_info {};
class SyntheticAttribute : public Attribute_info {};
class SignatureAttribute : public Attribute_info {};
class SourceFileAttribute : public Attribute_info {};
class SourceDebugExtensionAttribute : public Attribute_info {};
class LineNumberTableAttribute : public Attribute_info {};
class LocalVariableTableAttribute : public Attribute_info {};
class LocalVariableTypeTableAttribute : public Attribute_info {};
class DeprecatedAttribute : public Attribute_info {};
class RuntimeVisibleAnnotationsAttribute : public Attribute_info {};
class RuntimeInvisibleAnnotationsAttribute : public Attribute_info {};
class RuntimeVisibleParameterAnnotationsAttribute : public Attribute_info {};
class RuntimeInvisibleParameterAnnotationsAttribute : public Attribute_info {};
class RuntimeVisibleTypeAnnotationsAttribute : public Attribute_info {};
class RuntimeInvisibleTypeAnnotationsAttribute : public Attribute_info {};
class AnnotationDefaultAttribute : public Attribute_info {};
class BootstrapMethodsAttribute : public Attribute_info {};
class MethodParametersAttribute : public Attribute_info {};
class ModuleAttribute : public Attribute_info {};
class ModulePackagesAttribute : public Attribute_info {};
class ModuleMainClassAttribute : public Attribute_info {};
class NestHostAttribute : public Attribute_info {};
class NestMembersAttribute : public Attribute_info {};
class RecordAttribute : public Attribute_info {};

}

#endif