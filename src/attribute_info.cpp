#include "cfdump/attribute_info.hpp"

#include "cfdump/attributenameindextable.hpp"

//#include "cfdump/constantpool.hpp"
//#include "cfdump/constantpoolmember.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

Attribute_info::~Attribute_info() {if(info != nullptr) {delete[] info;}}

void Attribute_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    attribute_length = iou::GetNextBEU32(istr, err);
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

Attribute_info* Attribute_info::NewAttributeOfNameIndex(const uint16_t& index, const AttributeNameIndexTable& table) {
    Attribute_info* ret;
    if(index == table.ConstantValue) {ret = new ConstantValueAttribute();}
    else if(index == table.Code) {ret = new CodeAttribute();}
    else if(index == table.StackMapTable) {ret = new StackMapTableAttribute();}
    else if(index == table.Exceptions) {ret = new ExceptionsAttribute();}
    else if(index == table.InnerClasses) {ret = new InnerClassesAttribute();}
    else if(index == table.EnclosingMethod) {ret = new EnclosingMethodAttribute();}
    else if(index == table.Synthetic) {ret = new SyntheticAttribute();}
    else if(index == table.Signature) {ret = new SignatureAttribute();}
    else if(index == table.SourceFile) {ret = new SourceFileAttribute();}
    else if(index == table.SourceDebugExtension) {ret = new SourceDebugExtensionAttribute();}
    else if(index == table.LineNumberTable) {ret = new LineNumberTableAttribute();}
    else if(index == table.LocalVariableTable) {ret = new LocalVariableTableAttribute();}
    else if(index == table.LocalVariableTypeTable) {ret = new LocalVariableTypeTableAttribute();}
    else if(index == table.Deprecated) {ret = new DeprecatedAttribute();}
    else if(index == table.RuntimeVisibleAnnotations) {ret = new RuntimeVisibleAnnotationsAttribute();}
    else if(index == table.RuntimeInvisibleAnnotations) {ret = new RuntimeInvisibleAnnotationsAttribute();}
    else if(index == table.RuntimeVisibleParameterAnnotations) {ret = new RuntimeVisibleParameterAnnotationsAttribute();}
    else if(index == table.RuntimeInvisibleParameterAnnotations) {ret = new RuntimeInvisibleParameterAnnotationsAttribute();}
    else if(index == table.RuntimeVisibleTypeAnnotations) {ret = new RuntimeVisibleTypeAnnotationsAttribute();}
    else if(index == table.RuntimeInvisibleTypeAnnotations) {ret = new RuntimeInvisibleTypeAnnotationsAttribute();}
    else if(index == table.AnnotationDefault) {ret = new AnnotationDefaultAttribute();}
    else if(index == table.BootstrapMethods) {ret = new BootstrapMethodsAttribute();}
    else if(index == table.MethodParameters) {ret = new MethodParametersAttribute();}
    else if(index == table.Module) {ret = new ModuleAttribute();}
    else if(index == table.ModulePackages) {ret = new ModulePackagesAttribute();}
    else if(index == table.ModuleMainClass) {ret = new ModuleMainClassAttribute();}
    else if(index == table.NestHost) {ret = new NestHostAttribute();}
    else if(index == table.NestMembers) {ret = new NestMembersAttribute();}
    else if(index == table.Record) {ret = new RecordAttribute();}
    else {
        ret = new Attribute_info();
    }
    ret->attribute_name_index = index;
    return ret;
}

}