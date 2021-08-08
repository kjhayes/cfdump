#include "cfdump/constantpool.hpp"

#include<string>
#include<vector>
#include "cfdump/constantpoolmember.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/streamwrite.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

ConstantPool::ConstantPool(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}
ConstantPool::~ConstantPool() {
    for(auto iter = members.begin(); iter != members.end(); iter++){
        if(*iter != nullptr){
            delete *iter;
        }
    }
}

uint16_t ConstantPool::GetNumberOfEntries() const {
    uint16_t count = 0;
    for(auto iter = members.begin(); iter != members.end(); iter++){
        count += (*iter)->NumberOfCPEntriesTaken();
    }
    return count;
}
uint16_t ConstantPool::GetCount() const {
    return GetNumberOfEntries() + 1;
}

uint16_t ConstantPool::GetIndexOfMember(ConstantPoolMember* member) const {
    int i = 1;
    for(auto iter = members.begin(); iter != members.end(); iter++){
        if(member = (*iter)){return i;}
        else{
            i+=((*iter)->NumberOfCPEntriesTaken());
        }
    }
    return 0;
}
ConstantPoolMember* ConstantPool::GetMemberAtIndex(const uint16_t& index) const {
    uint16_t i = 1;
    for(auto iter = members.begin(); iter != members.end(); iter++){
        if(index == i){return (*iter);}
        else{
            i += (*iter)->NumberOfCPEntriesTaken();
        }
    }
    return nullptr;
}

void ConstantPool::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    uint16_t count = iou::GetNextBEU16(istr, err);
    int i = 0;
    uint16_t number_of_cp_entries_taken;
    while(i<count-1){
        ConstantPoolMember* m = ConstantPoolMember::NewConstantPoolMember(istr, err);
        number_of_cp_entries_taken = m->NumberOfCPEntriesTaken();
        members.push_back(m);
        i += number_of_cp_entries_taken;
    }
    std::vector<ConstantPoolMember*> vec_pool;
    for(auto iter = members.begin(); iter != members.end(); iter++){
        vec_pool.push_back((*iter));
    }
    for(auto iter = members.begin(); iter != members.end(); iter++){
        (*iter)->ResolveIndexReferences(this);
    }
}
void ConstantPool::WriteToBinaryStream(std::ostream& ostr) const {
    iou::PutBEU16(ostr, GetCount());
    for(auto iter = members.begin(); iter != members.end(); iter++){
        (*iter)->WriteToBinaryStream(ostr);
    }
}
void ConstantPool::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    uint16_t i = 1;
    uint16_t count = GetCount();
    for(auto iter = members.begin(); iter != members.end(); iter++){
        iou::JSON::WriteJSONObject(ostr, (std::string("Index ")+std::to_string(i+1)).c_str(), *(*iter), formatting, (i == (count-1)));
        i += (*iter)->NumberOfCPEntriesTaken();
    }
}

}