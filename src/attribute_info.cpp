#include "cfdump/attribute_info.hpp"

#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

Attribute_info::~Attribute_info() {if(info != nullptr) {delete[] info;}}
void Attribute_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    DefaultAttributeRead(istr, err);
    if(attribute_length > 0){
        info = new uint8_t[attribute_length];
        for(int i = 0; i<attribute_length; i++){
            info[i] = iou::GetNextU8(istr);
        }
    }
}
void Attribute_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Attribute Name", "Unknown", formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", attribute_name_index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Byte Length", attribute_length, formatting, (info==nullptr));
    if(info != nullptr){
        iou::JSON::BeginWriteJSONArray(ostr, "Data", formatting);
        for(int i = 0; i < attribute_length; i++){
            iou::JSON::WriteJSONArrayHex(ostr, info[i], formatting, (i == (attribute_length-1)));
        }
        iou::JSON::EndWriteJSONArray(ostr, formatting, true);
    }
}

void Attribute_info::DefaultAttributeRead(std::istream& istr, std::ostream& err) {
    attribute_name_index = iou::GetNextBEU16(istr, err);
    attribute_length = iou::GetNextBEU32(istr, err);
}

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