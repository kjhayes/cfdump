#include "cfdump/constantpool.hpp"

#include<string>
#include "cfdump/constantpoolmember.hpp"
#include "iostream-util/streamread.hpp"
#include "iostream-util/json.hpp"

namespace cfd {

ConstantPool::ConstantPool(std::istream& istr, std::ostream& err){ReadFromBinaryStream(istr, err);}
ConstantPool::~ConstantPool() {
    if(members != nullptr){
        for(int i = 0; i<number_of_members; i++){
            if(members[i] != nullptr) {delete members[i];}
        }
        delete[] members;
    }
}
ConstantPoolMember* ConstantPool::GetMember_PoolIndex(const int& index) {return members[index-1];}
ConstantPoolMember* ConstantPool::GetMember_ArrayIndex(const int& index) {return members[index];}

int ConstantPool::GetCount() {return count;}
int ConstantPool::GetNumberOfMembers() {return number_of_members;}

void ConstantPool::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    count = iou::GetNextBEU16(istr);
    number_of_members = count-1;
    members = new ConstantPoolMember*[count-1];
    int i = 0;
    int number_of_cp_entries_taken;
    while(i<count-1){
        members[i] = ConstantPoolMember::GetConstantPoolMember(istr, err);
        number_of_cp_entries_taken = members[i]->NumberOfCPEntriesTaken();
        for(int x = 1; x < number_of_cp_entries_taken; x++){
            members[i+1] = new UnusuableConstantPoolMember();
        }
        i += number_of_cp_entries_taken;
        if(i>count){err<<"ERROR: ConstantPool::ReadFromBinaryStream() Recieved More Constant Pool Members Than The .class File Indicated";}
    }
}
void ConstantPool::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    for(int i = 0; i < number_of_members; i++){
        iou::JSON::WriteJSONObject(ostr, (std::string("Index ")+std::to_string(i+1)).c_str(), *(members[i]), formatting, (i == number_of_members-1));
    }
}

}