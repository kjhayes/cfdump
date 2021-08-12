cmake_minimum_required(VERSION 3.19)

project(CFDUMP)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/iostream-util/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

add_executable(main ${CMAKE_SOURCE_DIR}/src/cfdump.cpp)
target_link_libraries(main ${CMAKE_PROJECT_NAME})