#include "cfdump/methodaccessflags.hpp"

#include "iostream-util/streamread.hpp"
#include "iostream-util/streamwrite.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

const char* MethodAccessFlags::MethodAccessStrings[12] = {
    "PUBLIC",       //0
    "PRIVATE",      //1
    "PROTECTED",    //2
    "STATIC",       //3
    "FINAL",        //4
    "SYNCHRONIZED",  //5
    "BRIDGE",       //6
    "VARARGS",      //7
    "NATIVE",       //8
    "ABSTRACT",     //9
    "STRICT",       //10
    "SYNTHETIC"     //11
};

void MethodAccessFlags::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    flags = iou::GetNextBEU16(istr, err);
}
void MethodAccessFlags::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutBEU16(ostr, flags);
}
void MethodAccessFlags::WriteJSON(std::ostream& ostr, const iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONHex(ostr, "Value", flags, formatting);
    iou::JSON::BeginWriteJSONStringStreamed(ostr, "Decoded", formatting);
    bool has_been_output = false;    
    const char* padding = " ";    
    if(flags & MethodAccessFlags::Enum::M_ABSTRACT) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[9];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_BRIDGE) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[6];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_FINAL) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[4];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_NATIVE) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[8];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_PRIVATE) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[1];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_PROTECTED) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[2];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_PUBLIC) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[0];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_STATIC) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[3];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_STRICT) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[10];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_SYNCHRONIZED) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[5];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_SYNTHETIC) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[11];has_been_output = true;}
    if(flags & MethodAccessFlags::Enum::M_VARARGS) {if(has_been_output){ostr<<padding;}ostr<<MethodAccessStrings[7];has_been_output = true;}
    iou::JSON::EndWriteJSONStringStreamed(ostr, formatting, true);
}

}