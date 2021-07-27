#include "cfdump/field_info.hpp"

#include "cfdump/attribute_info.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"
#include<string>

namespace cfd {

Field_info::Field_info(){}
Field_info::Field_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}
Field_info::~Field_info() {
    if(attributes != nullptr){
        delete[] attributes;
    }
}

void Field_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    access_flags.ReadFromBinaryStream(istr, err);
    name_index = iou::GetNextBEU16(istr);
    descriptor_index = iou::GetNextBEU16(istr);
    attributes_count = iou::GetNextBEU16(istr);
    if(attributes_count > 0){
        attributes = new Attribute_info[attributes_count];
        for(int i = 0; i<attributes_count; i++){
            attributes[i].ReadFromBinaryStream(istr, err);
        }
    }
}
void Field_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONObject(ostr, "Access Flags", access_flags, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Descriptor Index", descriptor_index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Attributes Count", attributes_count, formatting, (attributes_count == 0));
    if(attributes_count > 0){
        for(int i = 0; i < attributes_count; i++){
            iou::JSON::WriteJSONObject(ostr, (std::string("Attribute ")+std::to_string(i)).c_str(), attributes[i], formatting, (i==(attributes_count-1)));
        }
    }
}
}