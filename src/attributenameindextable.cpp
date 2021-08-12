#include "cfdump/attributenameindextable.hpp"

#include "cfdump/constantpoolmember.hpp"
#include<string>

namespace cfd {
    
AttributeNameIndexTable* AttributeNameIndexTable::last_set_table = nullptr;
void AttributeNameIndexTable::SetFromConstantPool(ConstantPool& pool) {
    last_set_table = this;
    size_t pool_count = pool.GetCount();
    int i = 1;
    while(i < pool_count){
        ConstantPoolMember* mem = pool.GetMemberAtIndex(i);
        if(mem->GetIndexOfTag() == 1){
            Utf8_info* utf = dynamic_cast<Utf8_info*>(pool.GetMemberAtIndex(i));
            if(utf->string.compare("ConstantValue") == 0){ConstantValue = i;}
            else if(utf->string.compare("Code") == 0){Code = i;}
            else if(utf->string.compare("StackMapTable") == 0){StackMapTable = i;}
            else if(utf->string.compare("Exceptions") == 0){Exceptions = i;}
            else if(utf->string.compare("InnerClasses") == 0){InnerClasses = i;}
            else if(utf->string.compare("EnclosingMethod") == 0){EnclosingMethod = i;}
            else if(utf->string.compare("Synthetic") == 0){Synthetic = i;}
            else if(utf->string.compare("Signature") == 0){Signature = i;}
            else if(utf->string.compare("SourceFile") == 0){SourceFile = i;}
            else if(utf->string.compare("SourceDebugExtension") == 0){SourceDebugExtension = i;}
            else if(utf->string.compare("LineNumberTable") == 0){LineNumberTable = i;}
            else if(utf->string.compare("LocalVariableTable") == 0){LocalVariableTable = i;}
            else if(utf->string.compare("LocalVariableTypeTable") == 0){LocalVariableTypeTable = i;}
            else if(utf->string.compare("Deprecated") == 0){Deprecated = i;}
            else if(utf->string.compare("RuntimeVisibleAnnotations") == 0){RuntimeVisibleAnnotations = i;}
            else if(utf->string.compare("RuntimeInvisibleAnnotations") == 0){RuntimeInvisibleAnnotations = i;}
            else if(utf->string.compare("RuntimeVisibleParameterAnnotations") == 0){RuntimeVisibleParameterAnnotations = i;}
            else if(utf->string.compare("RuntimeInvisibleParameterAnnotations") == 0){RuntimeInvisibleParameterAnnotations = i;}
            else if(utf->string.compare("RuntimeVisibleTypeAnnotations") == 0){RuntimeVisibleTypeAnnotations = i;}
            else if(utf->string.compare("RuntimeInvisibleTypeAnnotations") == 0){RuntimeInvisibleTypeAnnotations = i;}
            else if(utf->string.compare("AnnotationDefault") == 0){AnnotationDefault = i;}
            else if(utf->string.compare("BootstrapMethods") == 0){BootstrapMethods = i;}
            else if(utf->string.compare("MethodParameters") == 0){MethodParameters = i;}
            else if(utf->string.compare("Module") == 0){Module = i;}
            else if(utf->string.compare("ModulePackages") == 0){ModulePackages = i;}
            else if(utf->string.compare("ModuleMainClass") == 0){ModuleMainClass = i;}
            else if(utf->string.compare("NestHost") == 0){NestHost = i;}
            else if(utf->string.compare("NestMembers") == 0){NestMembers = i;}
            else if(utf->string.compare("Record") == 0){Record = i;}
        }
        i+=mem->NumberOfCPEntriesTaken();
    }
}

}