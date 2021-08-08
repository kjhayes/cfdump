#include "cfdump/attributenameindextable.hpp"

#include "cfdump/constantpoolmember.hpp"
#include<string>

namespace cfd {
    
AttributeNameIndexTable* AttributeNameIndexTable::last_set_table = nullptr;
void AttributeNameIndexTable::SetFromConstantPool(ConstantPool& pool) {
    last_set_table = this;
    size_t pool_count = pool.GetNumberOfMembers();
    for(int i = 0; i < pool_count; i++){
        if(pool.GetMember_ArrayIndex(i)->GetIndexOfTag() == 1){
            Utf8_info* utf = dynamic_cast<Utf8_info*>(pool.GetMember_ArrayIndex(i));
            std::string str((char*)(utf->data), utf->length);
            if(str.compare("ConstantValue") == 0){ConstantValue = i+1;}
            else if(str.compare("Code") == 0){Code = i+1;}
            else if(str.compare("StackMapTable") == 0){StackMapTable = i+1;}
            else if(str.compare("Exceptions") == 0){Exceptions = i+1;}
            else if(str.compare("InnerClasses") == 0){InnerClasses = i+1;}
            else if(str.compare("EnclosingMethod") == 0){EnclosingMethod = i+1;}
            else if(str.compare("Synthetic") == 0){Synthetic = i+1;}
            else if(str.compare("Signature") == 0){Signature = i+1;}
            else if(str.compare("SourceFile") == 0){SourceFile = i+1;}
            else if(str.compare("SourceDebugExtension") == 0){SourceDebugExtension = i+1;}
            else if(str.compare("LineNumberTable") == 0){LineNumberTable = i+1;}
            else if(str.compare("LocalVariableTable") == 0){LocalVariableTable = i+1;}
            else if(str.compare("LocalVariableTypeTable") == 0){LocalVariableTypeTable = i+1;}
            else if(str.compare("Deprecated") == 0){Deprecated = i+1;}
            else if(str.compare("RuntimeVisibleAnnotations") == 0){RuntimeVisibleAnnotations = i+1;}
            else if(str.compare("RuntimeInvisibleAnnotations") == 0){RuntimeInvisibleAnnotations = i+1;}
            else if(str.compare("RuntimeVisibleParameterAnnotations") == 0){RuntimeVisibleParameterAnnotations = i+1;}
            else if(str.compare("RuntimeInvisibleParameterAnnotations") == 0){RuntimeInvisibleParameterAnnotations = i+1;}
            else if(str.compare("RuntimeVisibleTypeAnnotations") == 0){RuntimeVisibleTypeAnnotations = i+1;}
            else if(str.compare("RuntimeInvisibleTypeAnnotations") == 0){RuntimeInvisibleTypeAnnotations = i+1;}
            else if(str.compare("AnnotationDefault") == 0){AnnotationDefault = i+1;}
            else if(str.compare("BootstrapMethods") == 0){BootstrapMethods = i+1;}
            else if(str.compare("MethodParameters") == 0){MethodParameters = i+1;}
            else if(str.compare("Module") == 0){Module = i+1;}
            else if(str.compare("ModulePackages") == 0){ModulePackages = i+1;}
            else if(str.compare("ModuleMainClass") == 0){ModuleMainClass = i+1;}
            else if(str.compare("NestHost") == 0){NestHost = i+1;}
            else if(str.compare("NestMembers") == 0){NestMembers = i+1;}
            else if(str.compare("Record") == 0){Record = i+1;}
        }
    }
}

}