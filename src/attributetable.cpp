#include "cfdump/attributetable.hpp"

#include "cfdump/attributenameindextable.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"

#include "cfdump/attribute_info.hpp"
#include "cfdump/attributenameindextable.hpp"

namespace cfd {

AttributeTable::~AttributeTable() {
    for(auto iter = attributes_info.begin(); iter != attributes_info.end(); iter++){
        delete (*iter);
    }
}

void AttributeTable::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    uint16_t attributes_count = iou::GetNextBEU16(istr, err);
    if(attributes_count > 0){
        for(int i = 0; i<attributes_count; i++){
            uint16_t attr_name_index = iou::GetNextBEU16(istr, err);
            Attribute_info* curr = Attribute_info::NewAttributeOfNameIndex(attr_name_index, *AttributeNameIndexTable::last_set_table);
            curr->ReadFromBinaryStream(istr, err);
            attributes_info.push_back(curr);
        }
    }
}

void AttributeTable::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Attribute Count", attributes_info.size(), formatting, (attributes_info.size() <= 0));
    if(attributes_info.size() > 0) {
        iou::JSON::BeginWriteJSONArray(ostr, "Attributes", formatting);
        int i = 0;
        for(auto iter = attributes_info.begin(); iter != attributes_info.end(); iter++){
            iou::JSON::WriteJSONArrayObject(ostr, *(*iter), formatting, (i == (attributes_info.size() - 1)));
            i++;
        }
        iou::JSON::EndWriteJSONArray(ostr, formatting, true);
    }   
}

}