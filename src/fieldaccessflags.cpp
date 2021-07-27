#include "cfdump/fieldaccessflags.hpp"

#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

const char* FieldAccessFlags::FieldAccessStrings[9] = {
    "PUBLIC",       //0
    "PRIVATE",      //1
    "PROTECTED",    //2
    "STATIC",       //3
    "FINAL",        //4
    "VOLATILE",     //5
    "TRANSIENT",    //6
    "SYNTHETIC",    //7
    "ENUM"          //8
};

void FieldAccessFlags::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    flags = iou::GetNextBEU16(istr, err);
}

void FieldAccessFlags::WriteJSON(std::ostream& ostr, const iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONHex(ostr, "Value", flags, formatting);
    iou::JSON::BeginWriteJSONStringStreamed(ostr, "Decoded", formatting);
    bool has_been_output = false;
    const char* padding = " ";
    if(flags & FieldAccessFlags::Enum::F_ENUM) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[8];has_been_output = true;}
    if(flags & FieldAccessFlags::Enum::F_FINAL) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[4];has_been_output = true;}
    if(flags & FieldAccessFlags::Enum::F_PRIVATE) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[1];has_been_output = true;}
    if(flags & FieldAccessFlags::Enum::F_PROTECTED) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[2];has_been_output = true;}
    if(flags & FieldAccessFlags::Enum::F_PUBLIC) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[0];has_been_output = true;}
    if(flags & FieldAccessFlags::Enum::F_STATIC) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[3];has_been_output = true;}
    if(flags & FieldAccessFlags::Enum::F_SYNTHETIC) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[7];has_been_output = true;}
    if(flags & FieldAccessFlags::Enum::F_TRANSIENT) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[6];has_been_output = true;}
    if(flags & FieldAccessFlags::Enum::F_VOLATILE) {if(has_been_output){ostr<<padding;}ostr<<FieldAccessStrings[5];has_been_output = true;}
    iou::JSON::EndWriteJSONStringStreamed(ostr, formatting, true);
}

}