#include "cfdump/exceptiontablemember.hpp"

#include "iostream-util/streamread.hpp"
#include "iostream-util/streamwrite.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

void ExceptionTableMember::ResolveIndexReferences(ConstantPool* pool) {
    catchtype.ResolveRead(pool);
}

void ExceptionTableMember::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    start_pc = iou::GetNextBEU16(istr, err);
    end_pc = iou::GetNextBEU16(istr, err);
    handler_pc = iou::GetNextBEU16(istr, err);
    catchtype.read_index = iou::GetNextBEU16(istr, err);
}
void ExceptionTableMember::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutBEU16(ostr, start_pc);
    iou::PutBEU16(ostr, end_pc);
    iou::PutBEU16(ostr, handler_pc);
    iou::PutBEU16(ostr, catchtype.Index());
}
void ExceptionTableMember::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Start PC", start_pc, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "End PC", end_pc, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Handler PC", handler_pc, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Catch Type Index", catchtype.Index(), formatting, true);
}

}