#include<fstream>
#include "cfdump/classfile_info.hpp"

int main(int argc, char** argv) {
    if(argc == 1){std::cerr<<"ERROR: No Argument Was Passed!"<<std::endl; return 1;}
    std::ifstream istr(argv[1], std::ios::binary);
    if(!istr.is_open()){std::cerr<<"ERROR: Could Not Open File: "<<argv[1]<<std::endl; return 1;}

    cfd::ClassFile_info classfile;
    classfile.ReadFromBinaryStream(istr);
    iou::JSONFormatting format;
    format.spacing = 0;
    format.write_arrays_inline = false;
    if(argc > 2){
        std::ofstream file(argv[2]);
        if(!file.is_open()){
            std::cerr<<"Could Not Open File: "<<argv[2]<<std::endl; return 1;
        }
        file.clear();
        file<<"{\n";
        classfile.WriteJSON(file, format);
        file<<"\n}";
    }
    else{
        std::cout<<"{\n";
        classfile.WriteJSON(std::cout, format);
        std::cout<<"\n}";
    }
    return 0;
}