#ifndef CFDUMP_ATTRIBUTE_INFO_HPP
#define CFDUMP_ATTRIBUTE_INFO_HPP

#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include<stdint.h>

namespace cfd {

struct AttributeNameIndexTable {
public:
    uint16_t ConstantValue = 0;
    uint16_t Code = 0;
    uint16_t StackMapTable = 0;
    uint16_t Exceptions = 0;
    uint16_t InnerClasses = 0;
    uint16_t EnclosingMethod = 0;
    uint16_t Synthetic = 0;
    uint16_t Signature = 0;
    uint16_t SourceFile = 0;
    uint16_t SourceDebugExtension = 0;
    uint16_t LineNumberTable = 0;
    uint16_t LocalVariableTable = 0;
    uint16_t LocalVariableTypeTable = 0;
    uint16_t Deprecated = 0;
    uint16_t RuntimeVisibleAnnotations = 0;
    uint16_t RuntimeInvisibleAnnotations = 0;
    uint16_t RuntimeVisibleParameterAnnotations = 0;
    uint16_t RuntimeInvisibleParameterAnnotations = 0;
    uint16_t RuntimeVisibleTypeAnnotations = 0;
    uint16_t RuntimeInvisibleTypeAnnotations = 0;
    uint16_t AnnotationDefault = 0;
    uint16_t BootstrapMethods = 0;
    uint16_t MethodParameters = 0;
    uint16_t Module = 0;
    uint16_t ModulePackages = 0;
    uint16_t ModuleMainClass = 0;
    uint16_t NestHost = 0;
    uint16_t NestMembers = 0;
    uint16_t Record = 0;
};

class Attribute_info : public iou::IBinaryReadable, public iou::IJSONWriteable {
public:
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t* info;

    static Attribute_info* NewAttributeOfNameIndex(const uint16_t& index, const AttributeNameIndexTable& table);
    virtual void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    virtual void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;

protected:
    virtual void DefaultAttributeRead(std::istream& istr, std::ostream& err = std::cerr);
};

class ConstantValueAttribute : public Attribute_info {};
class CodeAttribute : public Attribute_info {};
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
class UnknownAttribute : public Attribute_info {};

}

#endif