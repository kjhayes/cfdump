#include "cfdump/field_info.hpp"

#include "cfdump/attribute_info.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/streamwrite.hpp"
#include "iostream-util/json.hpp"
#include<string>

namespace cfd {

Field_info::Field_info(){}
Field_info::Field_info(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}

void Field_info::ResolveIndexReferences(ConstantPool* pool) {
    name_index.ResolveRead(pool);
    descriptor_index.ResolveRead(pool);
    attribute_table.ResolveIndexReferences(pool);
}

void Field_info::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    access_flags.ReadFromBinaryStream(istr, err);
    name_index.read_index = iou::GetNextBEU16(istr, err);
    descriptor_index.read_index = iou::GetNextBEU16(istr, err);
    attribute_table.ReadFromBinaryStream(istr, err);
}
void Field_info::WriteToBinaryStream(std::ostream& ostr) const {
    access_flags.WriteToBinaryStream(ostr);
    iou::PutBEU16(ostr, name_index.Index());
    iou::PutBEU16(ostr, descriptor_index.Index());
    attribute_table.WriteToBinaryStream(ostr);
}
void Field_info::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONObject(ostr, "Access Flags", access_flags, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Name Index", name_index.Index(), formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Descriptor Index", descriptor_index.Index(), formatting);
    iou::JSON::WriteJSONObject(ostr, "Attributes", attribute_table, formatting, true);
}
}