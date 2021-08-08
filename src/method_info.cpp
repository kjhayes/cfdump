#include "cfdump/method_info.hpp"

#include "cfdump/attribute_info.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"
#include<string>

#include "cfdump/attributenameindextable.hpp"

namespace cfd {

Method_info::Method_info(){}
Method_info::Method_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Method_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    access_flags.ReadFromBinaryStream(istr, err);
    name_index = iou::GetNextBEU16(istr, err);
    descriptor_index = iou::GetNextBEU16(istr, err);
    attribute_table.ReadFromBinaryStream(istr, err);
}
void Method_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONObject(ostr, "Access Flags", access_flags, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Descriptor Index", descriptor_index, formatting);
    iou::JSON::WriteJSONObject(ostr, "Attributes", attribute_table, formatting, true);
}
}