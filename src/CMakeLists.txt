cmake_minimum_required(VERSION 3.19)

add_library(${CMAKE_PROJECT_NAME} 
    attribute_info.cpp 
    classaccessflags.cpp 
    classfile.cpp
    codeattribute.cpp
    constantpool.cpp 
    constantpoolmember.cpp 
    field_info.cpp 
    fieldaccessflags.cpp
    jvmis.cpp 
    method_info.cpp 
    methodaccessflags.cpp
    )