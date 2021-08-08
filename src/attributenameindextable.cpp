#include "cfdump/attributenameindextable.hpp"

#include "cfdump/constantpoolmember.hpp"
#include<string>

namespace cfd {
    
AttributeNameIndexTable* AttributeNameIndexTable::last_set_table = nullptr;
void AttributeNameIndexTable::SetFromConstantPool(ConstantPool& pool) {
    last_set_table = this;
    size_t pool_count = pool.GetNumberOfEntries();
    for(int i = 0; i < pool_count; i++){
        if(pool.GetMemberAtIndex(i+1)->GetIndexOfTag() == 1){
            Utf8_info* utf = dynamic_cast<Utf8_info*>(pool.GetMemberAtIndex(i+1));
            if(utf->string.compare("ConstantValue") == 0){ConstantValue = i+1;}
            else if(utf->string.compare("Code") == 0){Code = i+1;}
            else if(utf->string.compare("StackMapTable") == 0){StackMapTable = i+1;}
            else if(utf->string.compare("Exceptions") == 0){Exceptions = i+1;}
            else if(utf->string.compare("InnerClasses") == 0){InnerClasses = i+1;}
            else if(utf->string.compare("EnclosingMethod") == 0){EnclosingMethod = i+1;}
            else if(utf->string.compare("Synthetic") == 0){Synthetic = i+1;}
            else if(utf->string.compare("Signature") == 0){Signature = i+1;}
            else if(utf->string.compare("SourceFile") == 0){SourceFile = i+1;}
            else if(utf->string.compare("SourceDebugExtension") == 0){SourceDebugExtension = i+1;}
            else if(utf->string.compare("LineNumberTable") == 0){LineNumberTable = i+1;}
            else if(utf->string.compare("LocalVariableTable") == 0){LocalVariableTable = i+1;}
            else if(utf->string.compare("LocalVariableTypeTable") == 0){LocalVariableTypeTable = i+1;}
            else if(utf->string.compare("Deprecated") == 0){Deprecated = i+1;}
            else if(utf->string.compare("RuntimeVisibleAnnotations") == 0){RuntimeVisibleAnnotations = i+1;}
            else if(utf->string.compare("RuntimeInvisibleAnnotations") == 0){RuntimeInvisibleAnnotations = i+1;}
            else if(utf->string.compare("RuntimeVisibleParameterAnnotations") == 0){RuntimeVisibleParameterAnnotations = i+1;}
            else if(utf->string.compare("RuntimeInvisibleParameterAnnotations") == 0){RuntimeInvisibleParameterAnnotations = i+1;}
            else if(utf->string.compare("RuntimeVisibleTypeAnnotations") == 0){RuntimeVisibleTypeAnnotations = i+1;}
            else if(utf->string.compare("RuntimeInvisibleTypeAnnotations") == 0){RuntimeInvisibleTypeAnnotations = i+1;}
            else if(utf->string.compare("AnnotationDefault") == 0){AnnotationDefault = i+1;}
            else if(utf->string.compare("BootstrapMethods") == 0){BootstrapMethods = i+1;}
            else if(utf->string.compare("MethodParameters") == 0){MethodParameters = i+1;}
            else if(utf->string.compare("Module") == 0){Module = i+1;}
            else if(utf->string.compare("ModulePackages") == 0){ModulePackages = i+1;}
            else if(utf->string.compare("ModuleMainClass") == 0){ModuleMainClass = i+1;}
            else if(utf->string.compare("NestHost") == 0){NestHost = i+1;}
            else if(utf->string.compare("NestMembers") == 0){NestMembers = i+1;}
            else if(utf->string.compare("Record") == 0){Record = i+1;}
        }
    }
}

}