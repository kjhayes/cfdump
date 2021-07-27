#include "cfdump/attribute_info.hpp"

#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

Attribute_info::Attribute_info(){}
Attribute_info::Attribute_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}
Attribute_info::~Attribute_info() {if(info != nullptr) {delete[] info;}}

void Attribute_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    attribute_name_index = iou::GetNextBEU16(istr);
    attribute_length = iou::GetNextBEU32(istr);
    if(attribute_length > 0){
        info = new uint8_t[attribute_length+1];
        for(int i = 0; i<attribute_length; i++){
            info[i] = iou::GetNextU8(istr);
        }
        info[attribute_length] = 0x00;
    }
}
void Attribute_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", attribute_name_index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Byte Length", attribute_length, formatting);
    if(info != nullptr){
        iou::JSON::WriteJSONString(ostr, "Data (UTF-8)", (char*)info, formatting, true);
    }
}

}