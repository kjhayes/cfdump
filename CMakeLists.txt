cmake_minimum_required(VERSION 3.19)

project(cfdump)

set(CMAKE_CXX_STANDARD 17)

set(CFDUMP_LIB_NAME cfdump)
set(CFDUMP_EXE_NAME cfd)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/iostream-util/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

add_executable(${CFDUMP_EXE_NAME} ${CMAKE_SOURCE_DIR}/src/cfdump.cpp)
target_link_libraries(${CFDUMP_EXE_NAME} ${CFDUMP_LIB_NAME})

install(TARGETS ${CFDUMP_LIB_NAME} TYPE LIBRARY)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include TYPE INCLUDE)