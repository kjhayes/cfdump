#include "cfdump/classaccessflags.hpp"

#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"
#include "iostream-util/streamwrite.hpp"

namespace cfd {

const char* ClassAccessFlags::ClassAccessStrings[9] = {
    "PUBLIC",       //0
    "FINAL",        //1
    "SUPER",        //2
    "INTERFACE",    //3
    "ABSTRACT",     //4
    "SYNTHETIC",    //5
    "ANNOTATION",   //6
    "ENUM",         //7
    "MODULE"        //8
};

void ClassAccessFlags::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    flags = iou::GetNextBEU16(istr, err);
}
void ClassAccessFlags::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutBEU16(ostr, flags);
}
void ClassAccessFlags::WriteJSON(std::ostream& ostr, const iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONHex(ostr, "Value", flags, formatting);
    iou::JSON::BeginWriteJSONStringStreamed(ostr, "Decoded", formatting);
    bool has_been_output = false;
    const char* padding = " ";
    if(flags & ClassAccessFlags::Enum::C_ABSTRACT) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[4];has_been_output = true;}
    if(flags & ClassAccessFlags::Enum::C_ANNOTATION) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[6];has_been_output = true;}
    if(flags & ClassAccessFlags::Enum::C_ENUM) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[7];has_been_output = true;}
    if(flags & ClassAccessFlags::Enum::C_FINAL) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[1];has_been_output = true;}
    if(flags & ClassAccessFlags::Enum::C_INTERFACE) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[3];has_been_output = true;}
    if(flags & ClassAccessFlags::Enum::C_PUBLIC) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[0];has_been_output = true;}
    if(flags & ClassAccessFlags::Enum::C_SUPER) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[2];has_been_output = true;}    
    if(flags & ClassAccessFlags::Enum::C_SYNTHETIC) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[5];has_been_output = true;}
    if(flags & ClassAccessFlags::Enum::C_MODULE) {if(has_been_output){ostr<<padding;}ostr<<ClassAccessStrings[8];has_been_output = true;}
    iou::JSON::EndWriteJSONStringStreamed(ostr, formatting, true);
}

}