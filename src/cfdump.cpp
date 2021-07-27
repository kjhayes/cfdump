#include<fstream>
#include "cfdump/classfile.hpp"

int main(int argc, char** argv) {
    if(argc == 1){std::cerr<<"ERROR: No Argument Was Passed!"<<std::endl; return 1;}
    std::ifstream istr(argv[1], std::ios::binary);

    cfd::ClassFile classfile;
    classfile.ReadFromBinaryStream(istr);
    iou::JSONFormatting format;
    classfile.WriteJSON(std::cout, format);
    return 0;
}