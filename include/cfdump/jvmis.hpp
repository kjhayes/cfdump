#ifndef CFDUMP_JVMIS_HPP
#define CFDUMP_JVMIS_HPP

#include "iostream-util/json.hpp"

#include<stdint.h>
#include "iostream-util/ibinaryreadable.hpp"
#include "iostream-util/ibinarywriteable.hpp"
#include "iostream-util/ijsonwriteable.hpp"
#include<list>

namespace cfd {
namespace jvmis{
enum OPCODE {
    op_aaload = 0x32,
    op_aastore = 0x53,
    op_aconst_null = 0x01,
    op_aload = 0x19,
    op_aload_0 = 0x2a,
    op_aload_1 = 0x2b,
    op_aload_2 = 0x2c,
    op_aload_3 = 0x2d,
    op_anewarray = 0xbd,
    op_areturn = 0xb0,
    op_arraylength = 0xbe,
    op_astore = 0x3a,
    op_astore_0 = 0x4b,
    op_astore_1 = 0x4c,
    op_astore_2 = 0x4d,
    op_astore_3 = 0x4e,
    op_athrow = 0xbf,
    op_baload = 0x33,
    op_bastore = 0x54,
    op_bipush = 0x10,
    op_breakpoint = 0xca,
    op_caload = 0x34,
    op_castore = 0x55,
    op_checkcast = 0xc0,
    op_d2f = 0x90,
    op_d2i = 0x8e,
    op_d2l = 0x8f,
    op_dadd = 0x63,
    op_daload = 0x31,
    op_dastore = 0x52,
    op_dcmpg = 0x98,
    op_dcmpl = 0x97,
    op_dconst_0 = 0x0e,
    op_dconst_1 = 0x0f,
    op_ddiv = 0x6f,
    op_dload = 0x18,
    op_dload_0 = 0x26,
    op_dload_1 = 0x27,
    op_dload_2 = 0x28,
    op_dload_3 = 0x29,
    op_dmul = 0x6b,
    op_dneg = 0x77,
    op_drem = 0x73,
    op_dreturn = 0xaf,
    op_dstore = 0x39,
    op_dstore_0 = 0x47,
    op_dstore_1 = 0x48,
    op_dstore_2 = 0x49,
    op_dstore_3 = 0x4a,
    op_dsub = 0x67,
    op_dup = 0x59,
    op_dup_x1 = 0x5a,
    op_dup_x2 = 0x5b,
    op_dup2 = 0x5c,
    op_dup2_x1 = 0x5d,
    op_dup2_x2 = 0x5e,
    op_f2d = 0x8d,
    op_f2i = 0x8b,
    op_f2l = 0x8c,
    op_fadd = 0x62,
    op_faload = 0x30,
    op_fastore = 0x51,
    op_fcmpg = 0x96,
    op_fcmpl = 0x95,
    op_fconst_0 = 0x0b,
    op_fconst_1 = 0x0c,
    op_fconst_2 = 0x0d,
    op_fdiv = 0x6e,
    op_fload = 0x17,
    op_fload_0 = 0x22,
    op_fload_1 = 0x23,
    op_fload_2 = 0x24,
    op_fload_3 = 0x25,
    op_fmul = 0x6a,
    op_fneg = 0x76,
    op_frem = 0x72,
    op_freturn = 0xae,
    op_fstore = 0x38,
    op_fstore_0 = 0x43,
    op_fstore_1 = 0x44,
    op_fstore_2 = 0x45,
    op_fstore_3 = 0x46,
    op_fsub = 0x66,
    op_getfield = 0xb4,
    op_getstatic = 0xb2,
    op_goto_ = 0xa7,
    op_goto_w = 0xc8,
    op_i2b = 0x91,
    op_i2c = 0x92,
    op_i2d = 0x87,
    op_i2f = 0x86,
    op_i2l = 0x85,
    op_i2s = 0x93,
    op_iadd = 0x60,
    op_iaload = 0x2e,
    op_iand = 0x7e,
    op_iastore = 0x4f,
    op_iconst_m1 = 0x02,
    op_iconst_0 = 0x03,
    op_iconst_1 = 0x04,
    op_iconst_2 = 0x05,
    op_iconst_3 = 0x06,
    op_iconst_4 = 0x07,
    op_iconst_5 = 0x08,
    op_idiv = 0x6c,
    op_if_acmpeq = 0xa5,
    op_if_acmpne = 0xa6,
    op_if_icmpeq = 0x9f,
    op_if_icmpge = 0xa2,
    op_if_icmpgt = 0xa3,
    op_if_icmple = 0xa4,
    op_if_icmplt = 0xa1,
    op_if_icmpne = 0xa0,
    op_ifeq = 0x99,
    op_ifge = 0x9c,
    op_ifgt = 0x9d,
    op_ifle = 0x9e,
    op_iflt = 0x9b,
    op_ifne = 0x9a,
    op_ifnonnull = 0xc7,
    op_ifnull = 0xc6,
    op_iinc = 0x84,
    op_iload = 0x15,
    op_iload_0 = 0x1a,
    op_iload_1 = 0x1b,
    op_iload_2 = 0x1c,
    op_iload_3 = 0x1d,
    op_impdep1 = 0xfe,
    op_impdep2 = 0xff,
    op_imul = 0x68,
    op_ineg = 0x74,
    op_instanceof = 0xc1,
    op_invokedynamic = 0xba,
    op_invokeinterface = 0xb9,
    op_invokespecial = 0xb7,
    op_invokestatic =  0xb8,
    op_invokevirtual = 0xb6,
    op_ior = 0x80,
    op_irem = 0x70,
    op_ireturn = 0xac,
    op_ishl = 0x78,
    op_ishr = 0x7a,
    op_istore = 0x36,
    op_istore_0 = 0x3b,
    op_istore_1 = 0x3c,
    op_istore_2 = 0x3d,
    op_istore_3 = 0x3e,
    op_isub = 0x64,
    op_iushr = 0x7c,
    op_ixor = 0x82,
    op_jsr = 0xa8, //deprecated 
    op_jsr_w = 0xc9, //deprecated
    op_l2d = 0x8a,
    op_l2f = 0x89,
    op_l2i = 0x88,
    op_ladd = 0x61,
    op_laload = 0x2f,
    op_land = 0x7f,
    op_lastore = 0x50,
    op_lcmp = 0x94,
    op_lconst_0 = 0x09,
    op_lconst_1 = 0x0a,
    op_ldc = 0x12,
    op_ldc_w = 0x13,
    op_ldc2_w = 0x14,
    op_ldiv = 0x6d,
    op_lload = 0x16,
    op_lload_0 = 0x1e,
    op_lload_1 = 0x1f,
    op_lload_2 = 0x20,
    op_lload_3 = 0x21,
    op_lmul = 0x69,
    op_lneg = 0x75,
    op_lookupswitch = 0xab,
    op_lor = 0x81,
    op_lrem = 0x71,
    op_lreturn = 0xad,
    op_lshl = 0x79,
    op_lshr = 0x7b,
    op_lstore = 0x37,
    op_lstore_0 = 0x3f,
    op_lstore_1 = 0x40,
    op_lstore_2 = 0x41,
    op_lstore_3 = 0x42,
    op_lsub = 0x65,
    op_lushr = 0x7d,
    op_lxor = 0x83,
    op_monitorenter = 0xc2,
    op_monitorexit = 0xc3,
    op_multianewarray = 0xc5,
    op_new_ = 0xbb,
    op_newarray = 0xbc,
    op_nop = 0x00,
    op_pop = 0x57,
    op_pop2 = 0x58,
    op_putfield = 0xb5,
    op_putstatic = 0xb3,
    op_ret = 0xa9, //deprecated
    op_return_ = 0xb1,
    op_saload = 0x35,
    op_sastore = 0x56,
    op_sipush = 0x11,
    op_swap = 0x5f,
    op_tableswitch = 0xaa,
    op_wide = 0xc4
};

class Instruction : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable {
public:
    virtual OPCODE Opcode() const = 0;
    virtual size_t ByteSize() const;
    virtual void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    virtual void WriteToBinaryStream(std::ostream& ostr) const override;
    virtual void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
    static Instruction* NewInstructionOfOpcode(const OPCODE& opcode);
    static const char* GetOPCODEString(const OPCODE& opcode);
    static size_t GetCodeLength(const std::list<Instruction*>& code);
};
class U8IndexedInstruction : public Instruction {
    uint8_t index;
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    virtual void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class U16IndexedInstruction : public Instruction {
    uint16_t index;
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    virtual void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class U16BranchedInstruction : public Instruction {
    uint16_t branch;
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    virtual void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class U32BranchedInstruction : public Instruction {
    uint32_t branch;
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    virtual void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};

//

class aaload : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_aaload;}
};
class aastore : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_aastore;}
};
class aconst_null : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_aconst_null;}
};
class aload : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_aload ;}
};
class aload_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_aload_0;}
};
class aload_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_aload_1;}
};
class aload_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_aload_2;}
};
class aload_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_aload_3;}
};
class anewarray : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_anewarray;}
};
class areturn : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_areturn;}
};
class arraylength : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_arraylength;}
};
class astore : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_astore;}
};
class astore_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_astore_0;}
};
class astore_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_astore_1;}
};
class astore_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_astore_2;}
};
class astore_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_astore_3;}
};
class athrow : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_athrow;}
};
class baload : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_baload;}
};
class bastore : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_bastore;}
};
class bipush : public Instruction {
    uint8_t byte;
    OPCODE Opcode() const override {return OPCODE::op_bipush;}
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class breakpoint : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_breakpoint;}
};
class caload : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_caload;}
};
class castore : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_castore;}
};
class checkcast : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_checkcast;}
};
class d2f : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_d2f;}
};
class d2i : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_d2i;}
};
class d2l : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_d2l;}
};
class dadd : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dadd;}
};
class daload : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_daload;}
};
class dastore : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dastore;}
};
class dcmpg : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dcmpg;}
};
class dcmpl : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dcmpl;}
};
class dconst_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dconst_0;}
};
class dconst_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dconst_1;}
};
class ddiv : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_ddiv;}
};
class dload : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_dload;}
};
class dload_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dload_0;}
};
class dload_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dload_1;}
};
class dload_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dload_2;}
};
class dload_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dload_3;}
};
class dmul : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dmul;}
};
class dneg : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dneg;}
};
class drem : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_drem;}
};
class dreturn : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dreturn;}
};
class dstore : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_dstore;}
};
class dstore_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dstore_0;}
};
class dstore_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dstore_1;}
};
class dstore_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dstore_2;}
};
class dstore_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dstore_3;}
};
class dsub : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dsub;}
};
class dup : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dup;}
};
class dup_x1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dup_x1;}
};
class dup_x2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dup_x2;}
};
class dup2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dup2;}
};
class dup2_x1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dup2_x1;}
};
class dup2_x2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_dup2_x2;}
};
class f2d : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_f2d;}
};
class f2i : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_f2i;}
};
class f2l : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_f2l;}
};
class fadd : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fadd;}
};
class faload : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_faload;}
};
class fastore : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fastore;}
};
class fcmpg : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fcmpg;}
};
class fcmpl : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fcmpl;}
};
class fconst_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fconst_0;}
};
class fconst_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fconst_1;}
};
class fconst_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fconst_2;}
};
class fdiv : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fdiv;}
};
class fload : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_fload;}
};
class fload_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fload_0;}
};
class fload_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fload_1;}
};
class fload_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fload_2;}
};
class fload_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fload_3;}
};
class fmul : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fmul;}
};
class fneg : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fneg;}
};
class frem : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_frem;}
};
class freturn : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_freturn;}
};
class fstore : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_fstore;}
};
class fstore_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fstore_0;}
};
class fstore_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fstore_1;}
};
class fstore_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fstore_2;}
};
class fstore_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fstore_3;}
};
class fsub : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_fsub;}
};
class getfield : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_getfield;}
};
class getstatic : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_getstatic;}
};
class goto_ : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_goto_;}
};
class goto_w : public U32BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_goto_w;}
};
class i2b : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_i2b;}
};
class i2c : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_i2c;}
};
class i2d : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_i2d;}
};
class i2f : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_i2f;}
};
class i2l : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_i2l;}
};
class i2s : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_i2s;}
};
class iadd : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iadd;}
};
class iaload : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iaload;}
};
class iand : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iand;}
};
class iastore : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iastore;}
};
class iconst_m1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iconst_m1;}
};
class iconst_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iconst_0;}
};
class iconst_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iconst_1;}
};
class iconst_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iconst_2;}
};
class iconst_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iconst_3;}
};
class iconst_4 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iconst_4;}
};
class iconst_5 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iconst_5;}
};
class idiv : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_idiv;}
};
class if_acmpeq : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_if_acmpeq;}
};
class if_acmpne : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_if_acmpne;}
};
class if_icmpeq : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_if_icmpeq;}
};
class if_icmpne : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_if_icmpne;}
};
class if_icmplt : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_if_icmplt;}
};
class if_icmpge : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_if_icmpge;}
};
class if_icmpgt : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_if_icmpgt;}
};
class if_icmple : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_if_icmple;}
};
class ifeq : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ifeq;}
};
class ifne : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ifne;}
};
class iflt : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_iflt;}
};
class ifge : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ifge;}
};
class ifgt : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ifgt;}
};
class ifle : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ifle;}
};
class ifnonnull : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ifnonnull;}
};
class ifnull : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ifnull;}
};
class iinc : public Instruction {
    uint8_t index;
    uint8_t byte;
    OPCODE Opcode() const override {return OPCODE::op_iinc;}
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class iload : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_iload;}
};
class iload_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iload_0;}
};
class iload_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iload_1;}
};
class iload_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iload_2;}
};
class iload_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iload_3;}
};
class impdep1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_impdep1;}
};
class impdep2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_impdep2;}
};
class imul : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_imul;}
};
class ineg : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_ineg;}
};
class instanceof : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_instanceof;}
};
class invokedynamic : public Instruction {
    uint16_t index;
    uint8_t zero_1;
    uint8_t zero_2;
    OPCODE Opcode() const override {return OPCODE::op_invokedynamic;}
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class invokeinterface : public Instruction {
    uint16_t index;
    uint8_t count;
    uint8_t zero;
    OPCODE Opcode() const override {return OPCODE::op_invokeinterface;}
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class invokespecial : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_invokespecial;}
};
class invokestatic : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_invokestatic;}
};
class invokevirtual : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_invokevirtual;}
};
class ior : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_ior;}
};
class irem : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_irem;}
};
class ireturn : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_ireturn;}
};
class ishl : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_ishl;}
};
class ishr : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_ishr;}
};
class istore : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_istore;}
};
class istore_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_istore_0;}
};
class istore_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_istore_1;}
};
class istore_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_istore_2;}
};
class istore_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_istore_3;}
};
class isub : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_isub;}
};
class iushr : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_iushr ;}
};
class ixor : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_ixor;}
};
class jsr : public U16BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_jsr;}
};
class jsr_w : public U32BranchedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_jsr_w ;}
};
class l2d : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_l2d;}
};
class l2f : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_l2f;}
};
class l2i : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_l2i;}
};
class ladd : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_ladd;}
};
class laload : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_laload;}
};
class land : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_land;}
};
class lastore : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lastore;}
};
class lcmp : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lcmp;}
};
class lconst_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lconst_0;}
};
class lconst_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lconst_1;}
};
class ldc : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ldc;}
};
class ldc_w : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ldc_w;}
};
class ldc2_w : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ldc2_w;}
};
class ldiv : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_ldiv;}
};
class lload : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_lload;}
};
class lload_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lload_0;}
};
class lload_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lload_1;}
};
class lload_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lload_2;}
};
class lload_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lload_3;}
};
class lmul : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lmul;}
};
class lneg : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lneg;}
};
struct lookupswitch_pair : public iou::IBinaryReadable, public iou::IJSONWriteable, public iou::IBinaryWriteable {
    int32_t match;
    int32_t offset;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class lookupswitch : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lookupswitch;}
    uint8_t number_of_padding_bytes;
    uint8_t padding_1;
    uint8_t padding_2;
    uint8_t padding_3;
    int32_t default_;
    std::list<lookupswitch_pair> pairs;
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class lor : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lor;}
};
class lrem : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lrem;}
};
class lreturn : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lreturn;}
};
class lshl : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lshl;}
};
class lshr : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lshr;}
};
class lstore : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_lstore;}
};
class lstore_0 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lstore_0;}
};
class lstore_1 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lstore_1;}
};
class lstore_2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lstore_2;}
};
class lstore_3 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lstore_3;}
};
class lsub : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lsub;}
};
class lushr : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lushr ;}
};
class lxor : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_lxor;}
};
class monitorenter : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_monitorenter;}
};
class monitorexit : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_monitorexit;}
};
class multianewarray : public Instruction {
    uint16_t index;
    uint8_t dimensions;
    OPCODE Opcode() const override {return OPCODE::op_multianewarray;}
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class new_ : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_new_;}
};
class newarray : public Instruction {
    uint8_t atype;
    OPCODE Opcode() const override {return OPCODE::op_newarray;}
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class nop : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_nop;}
};
class pop : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_pop;}
};
class pop2 : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_pop2;}
};
class putfield : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_putfield;}
};
class putstatic : public U16IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_putstatic;}
};
class ret : public U8IndexedInstruction {
    OPCODE Opcode() const override {return OPCODE::op_ret;}
};
class return_ : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_return_;}
};
class saload : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_saload;}
};
class sastore : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_sastore;}
};
class sipush : public Instruction {
    uint16_t short_;
    OPCODE Opcode() const override {return OPCODE::op_sipush;}
    size_t ByteSize() const override;
    void ReadFromBinaryStream(std::istream& istr, std::ostream& err = std::cerr) override;
    void WriteToBinaryStream(std::ostream& ostr) const override;
    void WriteJSON(std::ostream& ostr, iou::JSONFormatting formatting) const override;
};
class swap : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_swap;}
};
class tableswitch : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_tableswitch;}
};
class wide : public Instruction {
    OPCODE Opcode() const override {return OPCODE::op_wide;}
};

}
}

#endif