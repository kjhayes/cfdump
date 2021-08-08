cmake_minimum_required(VERSION 3.19)

add_library(${CMAKE_PROJECT_NAME} STATIC
    classaccessflags.cpp 
    classfile_info.cpp
    constantpool.cpp 
    constantpoolmember.cpp 
    field_info.cpp 
    fieldaccessflags.cpp
    jvmis.cpp 
    method_info.cpp 
    methodaccessflags.cpp
    exceptiontablemember.cpp
    attribute_info.cpp 
    attributenameindextable.cpp
    attributetable.cpp
    attributes/codeattribute.cpp
    )