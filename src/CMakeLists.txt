cmake_minimum_required(VERSION 3.19)

add_library(${CFDUMP_LIB_NAME} STATIC
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
    )

find_path(IOSTREAM_UTIL_INCLUDE_DIRS "iostream-util/ibinaryreadable.hpp" 
        PATH_SUFFIXES "installed/x86-windows/include/" "installed/x64-windows/include"
        REQUIRED)
target_include_directories(${CFDUMP_LIB_NAME} PUBLIC ${IOSTREAM_UTIL_INCLUDE_DIRS})     