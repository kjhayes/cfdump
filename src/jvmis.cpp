#include "cfdump/jvmis.hpp"

#include "iostream-util/json.hpp"
#include "iostream-util/streamread.hpp"
/*
aaload
aastore
aconst_null
aload
aload_0
aload_1
aload_2
aload_3
anewarray
areturn
arraylength 
astore
astore_0
astore_1
astore_2
astore_3
athrow
baload
bastore
bipush
breakpoint
caload
castore
checkcast
d2f
d2i
d2l
dadd
daload
dastore
dcmpg
dcmpl
dconst_0
dconst_1
ddiv
dload
dload_0
dload_1
dload_2
dload_3
dmul
dneg
drem
dreturn
dstore
dstore_0
dstore_1
dstore_2
dstore_3
dsub
dup
dup_x1
dup_x2
dup2
dup2_x1
dup2_x2
f2d
f2i
f2l
fadd
faload
fastore
fcmpg
fcmpl
fconst_0
fconst_1
fconst_2
fdiv
fload
fload_0
fload_1
fload_2
fload_3
fmul
fneg
frem
freturn
fstore
fstore_0
fstore_1
fstore_2
fstore_3
fsub
getfield
getstatic
goto_
goto_w
i2b
i2c
i2d
i2f
i2l
i2s
iadd
iaload
iand
iastore
iconst_m1
iconst_0 
iconst_1 
iconst_2 
iconst_3 
iconst_4 
iconst_5 
idiv
if_acmpeq
if_acmpne
if_icmpeq
if_icmpge
if_icmpgt
if_icmple
if_icmplt
if_icmpne
ifeq
ifge
ifgt
ifle
iflt
ifne
ifnonnull
ifnull
iinc
iload
iload_0
iload_1
iload_2
iload_3
impdep1
impdep2
imul
ineg
instanceof
invokedynamic 
invokeinterface
invokespecial 
invokestatic
invokevirtual 
ior
irem
ireturn
ishl
ishr
istore
istore_0
istore_1
istore_2
istore_3
isub
iushr
ixor
jsr
jsr_w 
l2d
l2f
l2i
ladd
laload
land
lastore
lcmp
lconst_0
lconst_1
ldc
ldc_w
ldc2_w
ldiv
lload
lload_0
lload_1
lload_2
lload_3
lmul
lneg
lookupswitch
lor
lrem
lreturn
lshl
lshr
lstore
lstore_0
lstore_1
lstore_2
lstore_3
lsub
lushr
lxor
monitorenter
monitorexit 
multianewarray
new_
newarray
nop
pop
pop2
putfield 
putstatic
ret
return_
saload 
sastore
sipush 
swap
tableswitch
wide
*/
namespace cfd {
namespace jvmis{

size_t Instruction::ByteSize() const {return 1;}
void Instruction::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {}
void Instruction::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Opcode", GetOPCODEString(Opcode()), formatting, true);
}

size_t U8IndexedInstruction::ByteSize() const {return 2;}
void U8IndexedInstruction::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    index = iou::GetNextU8(istr, err);
}
void U8IndexedInstruction::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Index", index, formatting, true);
} 

size_t U16IndexedInstruction::ByteSize() const {return 3;}
void U16IndexedInstruction::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    index = iou::GetNextBEU16(istr, err);
}
void U16IndexedInstruction::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Index", index, formatting, true);
} 

size_t U16BranchedInstruction::ByteSize() const {return 3;}
void U16BranchedInstruction::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    branch = iou::GetNextBEU16(istr, err);
}
void U16BranchedInstruction::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Branch", branch, formatting, true);
} 

size_t U32BranchedInstruction::ByteSize() const {return 4;}
void U32BranchedInstruction::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    branch = iou::GetNextBEU32(istr, err);
}
void U32BranchedInstruction::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Branch", branch, formatting, true);
}

size_t bipush::ByteSize() const {return 2;}
void bipush::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    byte = iou::GetNextU8(istr, err);
}
void bipush::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Byte", byte, formatting, true);
}

size_t iinc::ByteSize() const {return 3;}
void iinc::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    index = iou::GetNextU8(istr, err);
    byte = iou::GetNextU8(istr, err);
}
void iinc::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Index", index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Byte", byte, formatting, true);
}

size_t invokedynamic::ByteSize() const {return 5;}
void invokedynamic::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    index = iou::GetNextBEU16(istr, err);
    zero_1 = iou::GetNextU8(istr, err);
    zero_2 = iou::GetNextU8(istr, err);
}
void invokedynamic::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Index", index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Zero 1", zero_1, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Zero 2", zero_2, formatting, true);
}

size_t invokeinterface::ByteSize() const {return 5;}
void invokeinterface::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    index = iou::GetNextBEU16(istr, err);
    count = iou::GetNextU8(istr, err);
    zero = iou::GetNextU8(istr, err);
}
void invokeinterface::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Index", index, formatting);
    iou::JSON::WriteJSONUnsigned(ostr, "Count", count, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Zero", zero, formatting, true);
}

void lookupswitch_pair::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    match = iou::GetNextBEU32(istr, err);
    offset = iou::GetNextBEU32(istr, err);
}
void lookupswitch_pair::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONSigned(ostr, "Match", match, formatting);
    iou::JSON::WriteJSONSigned(ostr, "Offset", offset, formatting, true);
}

size_t lookupswitch::ByteSize() const {return number_of_padding_bytes + 8 + (pairs.size() * 8);}    
void lookupswitch::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    std::streampos pos = istr.tellg();
    number_of_padding_bytes = pos % 4;
    if(number_of_padding_bytes>0){
        padding_1 = iou::GetNextU8(istr, err);
        if(number_of_padding_bytes>1){
            padding_2 = iou::GetNextU8(istr, err);
            if(number_of_padding_bytes>2)
            {padding_3 = iou::GetNextU8(istr, err);
            }
        }
    }
    default = iou::GetNextBEU32(istr, err);
    int32_t npairs = iou::GetNextBEU32(istr, err);
    pairs.clear();
    for(int i = 0; i < npairs; i++){
        lookupswitch_pair pair;
        pair.ReadFromBinaryStream(istr, err);
        pairs.push_back(pair);
    }
}
void lookupswitch::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONString(ostr, "Opcode", GetOPCODEString(Opcode()), formatting);
    if(number_of_padding_bytes > 0){
    iou::JSON::BeginWriteJSONArray(ostr, "Padding Bytes", formatting);
    iou::JSON::WriteJSONArrayHex(ostr, padding_1, formatting, number_of_padding_bytes == 1);
    if(number_of_padding_bytes > 1){
        iou::JSON::WriteJSONArrayHex(ostr, padding_2, formatting, number_of_padding_bytes == 2);
        if(number_of_padding_bytes > 2){
            iou::JSON::WriteJSONArrayHex(ostr, padding_3, formatting, true);
        }
    }
    iou::JSON::EndWriteJSONArray(ostr, formatting);
    }
    iou::JSON::WriteJSONSigned(ostr, "Default", default, formatting);
    uint32_t npairs = pairs.size();
    iou::JSON::WriteJSONSigned(ostr, "Number Of Pairs", npairs, formatting, (npairs <= 0));
    if(npairs > 0){
        iou::JSON::BeginWriteJSONArray(ostr, "Pairs", formatting);
        for(int i = 0; i < npairs; i++){
            iou::JSON::WriteJSONArrayObject(ostr, pairs[i], formatting, i == (npairs-1));
        }
        iou::JSON::EndWriteJSONArray(ostr, formatting, true);
    }
}

size_t multianewarray::ByteSize() const {return 4;}
void multianewarray::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    index = iou::GetNextBEU16(istr, err);
    dimensions = iou::GetNextU8(istr, err);
}
void multianewarray::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Index", index, formatting, true);
    iou::JSON::WriteJSONUnsigned(ostr, "Dimensions", dimensions, formatting, true);
}

size_t newarray::ByteSize() const {return 2;}
void newarray::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    atype = iou::GetNextU8(istr, err);
}
void newarray::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "AType", atype, formatting, true);
}

size_t sipush::ByteSize() const {return 3;}
void sipush::ReadFromBinaryStream(std::istream& istr, std::ostream& err) {
    short_ = iou::GetNextU8(istr, err);
}
void sipush::WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const {
    iou::JSON::WriteJSONUnsigned(ostr, "Short", short_, formatting, true);
}

//

Instruction* Instruction::NewInstructionOfOpcode(const OPCODE& opcode) {
    switch(opcode){
        case(OPCODE::op_aaload):{return new aaload();}
        case(OPCODE::op_aastore):{return new aastore();}
        case(OPCODE::op_aconst_null):{return new aconst_null();}
        case(OPCODE::op_aload):{return new aload();}
        case(OPCODE::op_aload_0):{return new aload_0();}
        case(OPCODE::op_aload_1):{return new aload_1();}
        case(OPCODE::op_aload_2):{return new aload_2();}
        case(OPCODE::op_aload_3):{return new aload_3();}
        case(OPCODE::op_anewarray):{return new anewarray();}
        case(OPCODE::op_areturn):{return new areturn();}
        case(OPCODE::op_arraylength ):{return new arraylength();}
        case(OPCODE::op_astore):{return new astore();}
        case(OPCODE::op_astore_0):{return new astore_0();}
        case(OPCODE::op_astore_1):{return new astore_1();}
        case(OPCODE::op_astore_2):{return new astore_2();}
        case(OPCODE::op_astore_3):{return new astore_3();}
        case(OPCODE::op_athrow):{return new athrow();}
        case(OPCODE::op_baload):{return new baload();}
        case(OPCODE::op_bastore):{return new bastore();}
        case(OPCODE::op_bipush):{return new bipush();}
        case(OPCODE::op_breakpoint):{return new breakpoint();}
        case(OPCODE::op_caload):{return new caload();}
        case(OPCODE::op_castore):{return new castore();}
        case(OPCODE::op_checkcast):{return new checkcast();}
        case(OPCODE::op_d2f):{return new d2f();}
        case(OPCODE::op_d2i):{return new d2i();}
        case(OPCODE::op_d2l):{return new d2l();}
        case(OPCODE::op_dadd):{return new dadd();}
        case(OPCODE::op_daload):{return new daload();}
        case(OPCODE::op_dastore):{return new dastore();}
        case(OPCODE::op_dcmpg):{return new dcmpg();}
        case(OPCODE::op_dcmpl):{return new dcmpl();}
        case(OPCODE::op_dconst_0):{return new dconst_0();}
        case(OPCODE::op_dconst_1):{return new dconst_1();}
        case(OPCODE::op_ddiv):{return new ddiv();}
        case(OPCODE::op_dload):{return new dload();}
        case(OPCODE::op_dload_0):{return new dload_0();}
        case(OPCODE::op_dload_1):{return new dload_1();}
        case(OPCODE::op_dload_2):{return new dload_2();}
        case(OPCODE::op_dload_3):{return new dload_3();}
        case(OPCODE::op_dmul):{return new dmul();}
        case(OPCODE::op_dneg):{return new dneg();}
        case(OPCODE::op_drem):{return new drem();}
        case(OPCODE::op_dreturn):{return new dreturn();}
        case(OPCODE::op_dstore):{return new dstore();}
        case(OPCODE::op_dstore_0):{return new dstore_0();}
        case(OPCODE::op_dstore_1):{return new dstore_1();}
        case(OPCODE::op_dstore_2):{return new dstore_2();}
        case(OPCODE::op_dstore_3):{return new dstore_3();}
        case(OPCODE::op_dsub):{return new dsub();}
        case(OPCODE::op_dup):{return new dup();}
        case(OPCODE::op_dup_x1):{return new dup_x1();}
        case(OPCODE::op_dup_x2):{return new dup_x2();}
        case(OPCODE::op_dup2):{return new dup2();}
        case(OPCODE::op_dup2_x1):{return new dup2_x1();}
        case(OPCODE::op_dup2_x2):{return new dup2_x2();}
        case(OPCODE::op_f2d):{return new f2d();}
        case(OPCODE::op_f2i):{return new f2i();}
        case(OPCODE::op_f2l):{return new f2l();}
        case(OPCODE::op_fadd):{return new fadd();}
        case(OPCODE::op_faload):{return new faload();}
        case(OPCODE::op_fastore):{return new fastore();}
        case(OPCODE::op_fcmpg):{return new fcmpg();}
        case(OPCODE::op_fcmpl):{return new fcmpl();}
        case(OPCODE::op_fconst_0):{return new fconst_0();}
        case(OPCODE::op_fconst_1):{return new fconst_1();}
        case(OPCODE::op_fconst_2):{return new fconst_2();}
        case(OPCODE::op_fdiv):{return new fdiv();}
        case(OPCODE::op_fload):{return new fload();}
        case(OPCODE::op_fload_0):{return new fload_0();}
        case(OPCODE::op_fload_1):{return new fload_1();}
        case(OPCODE::op_fload_2):{return new fload_2();}
        case(OPCODE::op_fload_3):{return new fload_3();}
        case(OPCODE::op_fmul):{return new fmul();}
        case(OPCODE::op_fneg):{return new fneg();}
        case(OPCODE::op_frem):{return new frem();}
        case(OPCODE::op_freturn):{return new freturn();}
        case(OPCODE::op_fstore):{return new fstore();}
        case(OPCODE::op_fstore_0):{return new fstore_0();}
        case(OPCODE::op_fstore_1):{return new fstore_1();}
        case(OPCODE::op_fstore_2):{return new fstore_2();}
        case(OPCODE::op_fstore_3):{return new fstore_3();}
        case(OPCODE::op_fsub):{return new fsub();}
        case(OPCODE::op_getfield):{return new getfield();}
        case(OPCODE::op_getstatic):{return new getstatic();}
        case(OPCODE::op_goto_):{return new goto_();}
        case(OPCODE::op_goto_w):{return new goto_w();}
        case(OPCODE::op_i2b):{return new i2b();}
        case(OPCODE::op_i2c):{return new i2c();}
        case(OPCODE::op_i2d):{return new i2d();}
        case(OPCODE::op_i2f):{return new i2f();}
        case(OPCODE::op_i2l):{return new i2l();}
        case(OPCODE::op_i2s):{return new i2s();}
        case(OPCODE::op_iadd):{return new iadd();}
        case(OPCODE::op_iaload):{return new iaload();}
        case(OPCODE::op_iand):{return new iand();}
        case(OPCODE::op_iastore):{return new iastore();}
        case(OPCODE::op_iconst_m1):{return new iconst_m1();}
        case(OPCODE::op_iconst_0 ):{return new iconst_0();}
        case(OPCODE::op_iconst_1 ):{return new iconst_1();}
        case(OPCODE::op_iconst_2 ):{return new iconst_2();}
        case(OPCODE::op_iconst_3 ):{return new iconst_3();}
        case(OPCODE::op_iconst_4 ):{return new iconst_4();}
        case(OPCODE::op_iconst_5 ):{return new iconst_5();}
        case(OPCODE::op_idiv):{return new idiv();}
        case(OPCODE::op_if_acmpeq):{return new if_acmpeq();}
        case(OPCODE::op_if_acmpne):{return new if_acmpne();}
        case(OPCODE::op_if_icmpeq):{return new if_icmpeq();}
        case(OPCODE::op_if_icmpge):{return new if_icmpge();}
        case(OPCODE::op_if_icmpgt):{return new if_icmpgt();}
        case(OPCODE::op_if_icmple):{return new if_icmple();}
        case(OPCODE::op_if_icmplt):{return new if_icmplt();}
        case(OPCODE::op_if_icmpne):{return new if_icmpne();}
        case(OPCODE::op_ifeq):{return new ifeq();}
        case(OPCODE::op_ifge):{return new ifge();}
        case(OPCODE::op_ifgt):{return new ifgt();}
        case(OPCODE::op_ifle):{return new ifle();}
        case(OPCODE::op_iflt):{return new iflt();}
        case(OPCODE::op_ifne):{return new ifne();}
        case(OPCODE::op_ifnonnull):{return new ifnonnull();}
        case(OPCODE::op_ifnull):{return new ifnull();}
        case(OPCODE::op_iinc):{return new iinc();}
        case(OPCODE::op_iload):{return new iload();}
        case(OPCODE::op_iload_0):{return new iload_0();}
        case(OPCODE::op_iload_1):{return new iload_1();}
        case(OPCODE::op_iload_2):{return new iload_2();}
        case(OPCODE::op_iload_3):{return new iload_3();}
        case(OPCODE::op_impdep1):{return new impdep1();}
        case(OPCODE::op_impdep2):{return new impdep2();}
        case(OPCODE::op_imul):{return new imul();}
        case(OPCODE::op_ineg):{return new ineg();}
        case(OPCODE::op_instanceof):{return new instanceof();}
        case(OPCODE::op_invokedynamic):{return new invokedynamic();} 
        case(OPCODE::op_invokeinterface):{return new invokeinterface();}
        case(OPCODE::op_invokespecial):{return new invokespecial();} 
        case(OPCODE::op_invokestatic):{return new invokestatic();}
        case(OPCODE::op_invokevirtual):{return new invokevirtual();} 
        case(OPCODE::op_ior):{return new ior();}
        case(OPCODE::op_irem):{return new irem();}
        case(OPCODE::op_ireturn):{return new ireturn();}
        case(OPCODE::op_ishl):{return new ishl();}
        case(OPCODE::op_ishr):{return new ishr();}
        case(OPCODE::op_istore):{return new istore();}
        case(OPCODE::op_istore_0):{return new istore_0();}
        case(OPCODE::op_istore_1):{return new istore_1();}
        case(OPCODE::op_istore_2):{return new istore_2();}
        case(OPCODE::op_istore_3):{return new istore_3();}
        case(OPCODE::op_isub):{return new isub();}
        case(OPCODE::op_iushr):{return new iushr();}
        case(OPCODE::op_ixor):{return new ixor();}
        case(OPCODE::op_jsr):{return new jsr();}
        case(OPCODE::op_jsr_w ):{return new jsr_w();}
        case(OPCODE::op_l2d):{return new l2d();}
        case(OPCODE::op_l2f):{return new l2f();}
        case(OPCODE::op_l2i):{return new l2i();}
        case(OPCODE::op_ladd):{return new ladd();}
        case(OPCODE::op_laload):{return new laload();}
        case(OPCODE::op_land):{return new land();}
        case(OPCODE::op_lastore):{return new lastore();}
        case(OPCODE::op_lcmp):{return new lcmp();}
        case(OPCODE::op_lconst_0):{return new lconst_0();}
        case(OPCODE::op_lconst_1):{return new lconst_1();}
        case(OPCODE::op_ldc):{return new ldc();}
        case(OPCODE::op_ldc_w):{return new ldc_w();}
        case(OPCODE::op_ldc2_w):{return new ldc2_w();}
        case(OPCODE::op_ldiv):{return new ldiv();}
        case(OPCODE::op_lload):{return new lload();}
        case(OPCODE::op_lload_0):{return new lload_0();}
        case(OPCODE::op_lload_1):{return new lload_1();}
        case(OPCODE::op_lload_2):{return new lload_2();}
        case(OPCODE::op_lload_3):{return new lload_3();}
        case(OPCODE::op_lmul):{return new lmul();}
        case(OPCODE::op_lneg):{return new lneg();}
        case(OPCODE::op_lookupswitch):{return new lookupswitch();}
        case(OPCODE::op_lor):{return new lor();}
        case(OPCODE::op_lrem):{return new lrem();}
        case(OPCODE::op_lreturn):{return new lreturn();}
        case(OPCODE::op_lshl):{return new lshl();}
        case(OPCODE::op_lshr):{return new lshr();}
        case(OPCODE::op_lstore):{return new lstore();}
        case(OPCODE::op_lstore_0):{return new lstore_0();}
        case(OPCODE::op_lstore_1):{return new lstore_1();}
        case(OPCODE::op_lstore_2):{return new lstore_2();}
        case(OPCODE::op_lstore_3):{return new lstore_3();}
        case(OPCODE::op_lsub):{return new lsub();}
        case(OPCODE::op_lushr):{return new lushr();}
        case(OPCODE::op_lxor):{return new lxor();}
        case(OPCODE::op_monitorenter):{return new monitorenter();}
        case(OPCODE::op_monitorexit):{return new monitorexit();}
        case(OPCODE::op_multianewarray):{return new multianewarray();}
        case(OPCODE::op_new_):{return new new_();}
        case(OPCODE::op_newarray):{return new newarray();}
        case(OPCODE::op_nop):{return new nop();}
        case(OPCODE::op_pop):{return new pop();}
        case(OPCODE::op_pop2):{return new pop2();}
        case(OPCODE::op_putfield ):{return new putfield();}
        case(OPCODE::op_putstatic):{return new putstatic();}
        case(OPCODE::op_ret):{return new ret();}
        case(OPCODE::op_return_):{return new return_();}
        case(OPCODE::op_saload ):{return new saload();}
        case(OPCODE::op_sastore):{return new sastore();}
        case(OPCODE::op_sipush ):{return new sipush();}
        case(OPCODE::op_swap):{return new swap();}
        case(OPCODE::op_tableswitch):{return new tableswitch();}
        case(OPCODE::op_wide):{return new wide();}
    }
}
static const char* GetOPCODEString(const OPCODE& opcode){
    switch(opcode){
        case(OPCODE::op_aaload):{return "aaload";}
        case(OPCODE::op_aastore):{return "aastore";}
        case(OPCODE::op_aconst_null):{return "aconst_null";}
        case(OPCODE::op_aload):{return "aload";}
        case(OPCODE::op_aload_0):{return "aload_0";}
        case(OPCODE::op_aload_1):{return "aload_1";}
        case(OPCODE::op_aload_2):{return "aload_2";}
        case(OPCODE::op_aload_3):{return "aload_3";}
        case(OPCODE::op_anewarray):{return "anewarray";}
        case(OPCODE::op_areturn):{return "areturn";}
        case(OPCODE::op_arraylength ):{return "arraylength";}
        case(OPCODE::op_astore):{return "astore";}
        case(OPCODE::op_astore_0):{return "astore_0";}
        case(OPCODE::op_astore_1):{return "astore_1";}
        case(OPCODE::op_astore_2):{return "astore_2";}
        case(OPCODE::op_astore_3):{return "astore_3";}
        case(OPCODE::op_athrow):{return "athrow";}
        case(OPCODE::op_baload):{return "baload";}
        case(OPCODE::op_bastore):{return "bastore";}
        case(OPCODE::op_bipush):{return "bipush";}
        case(OPCODE::op_breakpoint):{return "breakpoint";}
        case(OPCODE::op_caload):{return "caload";}
        case(OPCODE::op_castore):{return "castore";}
        case(OPCODE::op_checkcast):{return "checkcast";}
        case(OPCODE::op_d2f):{return "d2f";}
        case(OPCODE::op_d2i):{return "d2i";}
        case(OPCODE::op_d2l):{return "d2l";}
        case(OPCODE::op_dadd):{return "dadd";}
        case(OPCODE::op_daload):{return "daload";}
        case(OPCODE::op_dastore):{return "dastore";}
        case(OPCODE::op_dcmpg):{return "dcmpg";}
        case(OPCODE::op_dcmpl):{return "dcmpl";}
        case(OPCODE::op_dconst_0):{return "dconst_0";}
        case(OPCODE::op_dconst_1):{return "dconst_1";}
        case(OPCODE::op_ddiv):{return "ddiv";}
        case(OPCODE::op_dload):{return "dload";}
        case(OPCODE::op_dload_0):{return "dload_0";}
        case(OPCODE::op_dload_1):{return "dload_1";}
        case(OPCODE::op_dload_2):{return "dload_2";}
        case(OPCODE::op_dload_3):{return "dload_3";}
        case(OPCODE::op_dmul):{return "dmul";}
        case(OPCODE::op_dneg):{return "dneg";}
        case(OPCODE::op_drem):{return "drem";}
        case(OPCODE::op_dreturn):{return "dreturn";}
        case(OPCODE::op_dstore):{return "dstore";}
        case(OPCODE::op_dstore_0):{return "dstore_0";}
        case(OPCODE::op_dstore_1):{return "dstore_1";}
        case(OPCODE::op_dstore_2):{return "dstore_2";}
        case(OPCODE::op_dstore_3):{return "dstore_3";}
        case(OPCODE::op_dsub):{return "dsub";}
        case(OPCODE::op_dup):{return "dup";}
        case(OPCODE::op_dup_x1):{return "dup_x1";}
        case(OPCODE::op_dup_x2):{return "dup_x2";}
        case(OPCODE::op_dup2):{return "dup2";}
        case(OPCODE::op_dup2_x1):{return "dup2_x1";}
        case(OPCODE::op_dup2_x2):{return "dup2_x2";}
        case(OPCODE::op_f2d):{return "f2d";}
        case(OPCODE::op_f2i):{return "f2i";}
        case(OPCODE::op_f2l):{return "f2l";}
        case(OPCODE::op_fadd):{return "fadd";}
        case(OPCODE::op_faload):{return "faload";}
        case(OPCODE::op_fastore):{return "fastore";}
        case(OPCODE::op_fcmpg):{return "fcmpg";}
        case(OPCODE::op_fcmpl):{return "fcmpl";}
        case(OPCODE::op_fconst_0):{return "fconst_0";}
        case(OPCODE::op_fconst_1):{return "fconst_1";}
        case(OPCODE::op_fconst_2):{return "fconst_2";}
        case(OPCODE::op_fdiv):{return "fdiv";}
        case(OPCODE::op_fload):{return "fload";}
        case(OPCODE::op_fload_0):{return "fload_0";}
        case(OPCODE::op_fload_1):{return "fload_1";}
        case(OPCODE::op_fload_2):{return "fload_2";}
        case(OPCODE::op_fload_3):{return "fload_3";}
        case(OPCODE::op_fmul):{return "fmul";}
        case(OPCODE::op_fneg):{return "fneg";}
        case(OPCODE::op_frem):{return "frem";}
        case(OPCODE::op_freturn):{return "freturn";}
        case(OPCODE::op_fstore):{return "fstore";}
        case(OPCODE::op_fstore_0):{return "fstore_0";}
        case(OPCODE::op_fstore_1):{return "fstore_1";}
        case(OPCODE::op_fstore_2):{return "fstore_2";}
        case(OPCODE::op_fstore_3):{return "fstore_3";}
        case(OPCODE::op_fsub):{return "fsub";}
        case(OPCODE::op_getfield):{return "getfield";}
        case(OPCODE::op_getstatic):{return "getstatic";}
        case(OPCODE::op_goto_):{return "goto_";}
        case(OPCODE::op_goto_w):{return "goto_w";}
        case(OPCODE::op_i2b):{return "i2b";}
        case(OPCODE::op_i2c):{return "i2c";}
        case(OPCODE::op_i2d):{return "i2d";}
        case(OPCODE::op_i2f):{return "i2f";}
        case(OPCODE::op_i2l):{return "i2l";}
        case(OPCODE::op_i2s):{return "i2s";}
        case(OPCODE::op_iadd):{return "iadd";}
        case(OPCODE::op_iaload):{return "iaload";}
        case(OPCODE::op_iand):{return "iand";}
        case(OPCODE::op_iastore):{return "iastore";}
        case(OPCODE::op_iconst_m1):{return "iconst_m1";}
        case(OPCODE::op_iconst_0 ):{return "iconst_0";}
        case(OPCODE::op_iconst_1 ):{return "iconst_1";}
        case(OPCODE::op_iconst_2 ):{return "iconst_2";}
        case(OPCODE::op_iconst_3 ):{return "iconst_3";}
        case(OPCODE::op_iconst_4 ):{return "iconst_4";}
        case(OPCODE::op_iconst_5 ):{return "iconst_5";}
        case(OPCODE::op_idiv):{return "idiv";}
        case(OPCODE::op_if_acmpeq):{return "if_acmpeq";}
        case(OPCODE::op_if_acmpne):{return "if_acmpne";}
        case(OPCODE::op_if_icmpeq):{return "if_icmpeq";}
        case(OPCODE::op_if_icmpge):{return "if_icmpge";}
        case(OPCODE::op_if_icmpgt):{return "if_icmpgt";}
        case(OPCODE::op_if_icmple):{return "if_icmple";}
        case(OPCODE::op_if_icmplt):{return "if_icmplt";}
        case(OPCODE::op_if_icmpne):{return "if_icmpne";}
        case(OPCODE::op_ifeq):{return "ifeq";}
        case(OPCODE::op_ifge):{return "ifge";}
        case(OPCODE::op_ifgt):{return "ifgt";}
        case(OPCODE::op_ifle):{return "ifle";}
        case(OPCODE::op_iflt):{return "iflt";}
        case(OPCODE::op_ifne):{return "ifne";}
        case(OPCODE::op_ifnonnull):{return "ifnonnull";}
        case(OPCODE::op_ifnull):{return "ifnull";}
        case(OPCODE::op_iinc):{return "iinc";}
        case(OPCODE::op_iload):{return "iload";}
        case(OPCODE::op_iload_0):{return "iload_0";}
        case(OPCODE::op_iload_1):{return "iload_1";}
        case(OPCODE::op_iload_2):{return "iload_2";}
        case(OPCODE::op_iload_3):{return "iload_3";}
        case(OPCODE::op_impdep1):{return "impdep1";}
        case(OPCODE::op_impdep2):{return "impdep2";}
        case(OPCODE::op_imul):{return "imul";}
        case(OPCODE::op_ineg):{return "ineg";}
        case(OPCODE::op_instanceof):{return "instanceof";}
        case(OPCODE::op_invokedynamic):{return "invokedynamic";} 
        case(OPCODE::op_invokeinterface):{return "invokeinterface";}
        case(OPCODE::op_invokespecial):{return "invokespecial";} 
        case(OPCODE::op_invokestatic):{return "invokestatic";}
        case(OPCODE::op_invokevirtual):{return "invokevirtual";} 
        case(OPCODE::op_ior):{return "ior";}
        case(OPCODE::op_irem):{return "irem";}
        case(OPCODE::op_ireturn):{return "ireturn";}
        case(OPCODE::op_ishl):{return "ishl";}
        case(OPCODE::op_ishr):{return "ishr";}
        case(OPCODE::op_istore):{return "istore";}
        case(OPCODE::op_istore_0):{return "istore_0";}
        case(OPCODE::op_istore_1):{return "istore_1";}
        case(OPCODE::op_istore_2):{return "istore_2";}
        case(OPCODE::op_istore_3):{return "istore_3";}
        case(OPCODE::op_isub):{return "isub";}
        case(OPCODE::op_iushr):{return "iushr";}
        case(OPCODE::op_ixor):{return "ixor";}
        case(OPCODE::op_jsr):{return "jsr";}
        case(OPCODE::op_jsr_w ):{return "jsr_w";}
        case(OPCODE::op_l2d):{return "l2d";}
        case(OPCODE::op_l2f):{return "l2f";}
        case(OPCODE::op_l2i):{return "l2i";}
        case(OPCODE::op_ladd):{return "ladd";}
        case(OPCODE::op_laload):{return "laload";}
        case(OPCODE::op_land):{return "land";}
        case(OPCODE::op_lastore):{return "lastore";}
        case(OPCODE::op_lcmp):{return "lcmp";}
        case(OPCODE::op_lconst_0):{return "lconst_0";}
        case(OPCODE::op_lconst_1):{return "lconst_1";}
        case(OPCODE::op_ldc):{return "ldc";}
        case(OPCODE::op_ldc_w):{return "ldc_w";}
        case(OPCODE::op_ldc2_w):{return "ldc2_w";}
        case(OPCODE::op_ldiv):{return "ldiv";}
        case(OPCODE::op_lload):{return "lload";}
        case(OPCODE::op_lload_0):{return "lload_0";}
        case(OPCODE::op_lload_1):{return "lload_1";}
        case(OPCODE::op_lload_2):{return "lload_2";}
        case(OPCODE::op_lload_3):{return "lload_3";}
        case(OPCODE::op_lmul):{return "lmul";}
        case(OPCODE::op_lneg):{return "lneg";}
        case(OPCODE::op_lookupswitch):{return "lookupswitch";}
        case(OPCODE::op_lor):{return "lor";}
        case(OPCODE::op_lrem):{return "lrem";}
        case(OPCODE::op_lreturn):{return "lreturn";}
        case(OPCODE::op_lshl):{return "lshl";}
        case(OPCODE::op_lshr):{return "lshr";}
        case(OPCODE::op_lstore):{return "lstore";}
        case(OPCODE::op_lstore_0):{return "lstore_0";}
        case(OPCODE::op_lstore_1):{return "lstore_1";}
        case(OPCODE::op_lstore_2):{return "lstore_2";}
        case(OPCODE::op_lstore_3):{return "lstore_3";}
        case(OPCODE::op_lsub):{return "lsub";}
        case(OPCODE::op_lushr):{return "lushr";}
        case(OPCODE::op_lxor):{return "lxor";}
        case(OPCODE::op_monitorenter):{return "monitorenter";}
        case(OPCODE::op_monitorexit):{return "monitorexit";}
        case(OPCODE::op_multianewarray):{return "multianewarray";}
        case(OPCODE::op_new_):{return "new_";}
        case(OPCODE::op_newarray):{return "newarray";}
        case(OPCODE::op_nop):{return "nop";}
        case(OPCODE::op_pop):{return "pop";}
        case(OPCODE::op_pop2):{return "pop2";}
        case(OPCODE::op_putfield ):{return "putfield";}
        case(OPCODE::op_putstatic):{return "putstatic";}
        case(OPCODE::op_ret):{return "ret";}
        case(OPCODE::op_return_):{return "return_";}
        case(OPCODE::op_saload ):{return "saload";}
        case(OPCODE::op_sastore):{return "sastore";}
        case(OPCODE::op_sipush ):{return "sipush";}
        case(OPCODE::op_swap):{return "swap";}
        case(OPCODE::op_tableswitch):{return "tableswitch";}
        case(OPCODE::op_wide):{return "wide";}
    }
}

}
}