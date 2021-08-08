#ifndef CFDUMP_ATTRIBUTENAMEINDEXTABLE_HPP
#define CFDUMP_ATTRIBUTENAMEINDEXTABLE_HPP

#include<cfdump/constantpool.hpp>

#include<stdint.h>

namespace cfd {

struct AttributeNameIndexTable {
public:
    static AttributeNameIndexTable* last_set_table;

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

    void SetFromConstantPool(ConstantPool& pool);
};

}

#endif