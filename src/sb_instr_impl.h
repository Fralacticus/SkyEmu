
// This file is autogenerated do not edit

#ifndef SB_INSTR_IMPL
#define SB_INSTR_IMPL 1

#include "sb_types.h"
#include <stdio.h>

#define SB_OP_0 0
#define SB_OP_00H 1
#define SB_OP_08H 2
#define SB_OP_1 3
#define SB_OP_10H 4
#define SB_OP_18H 5
#define SB_OP_2 6
#define SB_OP_20H 7
#define SB_OP_28H 8
#define SB_OP_3 9
#define SB_OP_30H 10
#define SB_OP_38H 11
#define SB_OP_4 12
#define SB_OP_5 13
#define SB_OP_6 14
#define SB_OP_7 15
#define SB_OP_A 16
#define SB_OP_AF 17
#define SB_OP_B 18
#define SB_OP_BC 19
#define SB_OP_BC_INDIRECT 20
#define SB_OP_C 21
#define SB_OP_C_FLAG 22
#define SB_OP_D 23
#define SB_OP_DE 24
#define SB_OP_DE_INDIRECT 25
#define SB_OP_E 26
#define SB_OP_FF00_PLUS_C_INDIRECT 27
#define SB_OP_FF00_PLUS_U8_INDIRECT 28
#define SB_OP_H 29
#define SB_OP_HL 30
#define SB_OP_HL_DEC_INDIRECT 31
#define SB_OP_HL_INC_INDIRECT 32
#define SB_OP_HL_INDIRECT 33
#define SB_OP_I8 34
#define SB_OP_L 35
#define SB_OP_NC_FLAG 36
#define SB_OP_NONE 37
#define SB_OP_NZ_FLAG 38
#define SB_OP_SP 39
#define SB_OP_SP_PLUS_I8 40
#define SB_OP_U16 41
#define SB_OP_U16_INDIRECT 42
#define SB_OP_U8 43
#define SB_OP_Z_FLAG 44

#define SB_Z_BIT 7U
#define SB_N_BIT 6U
#define SB_H_BIT 5U
#define SB_C_BIT 4U

uint16_t sb_read16(sb_gb_t *gb, int addr);
uint8_t sb_read8(sb_gb_t *gb, int addr);
void sb_store8(sb_gb_t *gb, int addr, int value);
void sb_store16(sb_gb_t *gb, int addr, unsigned int value);

void sb_set_flags(sb_gb_t *gb, const uint8_t* flag_mask, int Z, int N, int H, int C){
  
  if(flag_mask[0]=='-')Z=-1;
  if(flag_mask[1]=='-')N=-1;
  if(flag_mask[2]=='-')H=-1;
  if(flag_mask[3]=='-')C=-1;

  if(Z==-1)Z = (gb->cpu.af>>SB_Z_BIT)&1;
  if(N==-1)N = (gb->cpu.af>>SB_N_BIT)&1;
  if(H==-1)H = (gb->cpu.af>>SB_H_BIT)&1;
  if(C==-1)C = (gb->cpu.af>>SB_C_BIT)&1;
  
  Z &=1;
  N &=1;
  H &=1;
  C &=1;

  int flags = (Z<<SB_Z_BIT)|(N<<SB_N_BIT)|(H<<SB_H_BIT)|(C<<SB_C_BIT);
  gb->cpu.af = (gb->cpu.af&0xff00)|flags;
}
int sb_load_operand(sb_gb_t* gb, int operand){
  switch(operand){
    case SB_OP_0: { return 0; }
    case SB_OP_00H: { return 0; }
    case SB_OP_08H: { return 0x8; }
    case SB_OP_1: { return 1; }
    case SB_OP_10H: { return 0x10; }
    case SB_OP_18H: { return 0x18; }
    case SB_OP_2: { return 2; }
    case SB_OP_20H: { return 0x20; }
    case SB_OP_28H: { return 0x28; }
    case SB_OP_3: { return 3; }
    case SB_OP_30H: { return 0x30; }
    case SB_OP_38H: { return 0x38; }
    case SB_OP_4: { return 4; }
    case SB_OP_5: { return 5; }
    case SB_OP_6: { return 6; }
    case SB_OP_7: { return 7; }
    case SB_OP_A: { return SB_U16_HI(gb->cpu.af); }
    case SB_OP_AF: { return gb->cpu.af; }
    case SB_OP_B: { return SB_U16_HI(gb->cpu.bc); }
    case SB_OP_BC: { return gb->cpu.bc; }
    case SB_OP_BC_INDIRECT: { return sb_read8(gb,gb->cpu.bc); }
    case SB_OP_C: { return SB_U16_LO(gb->cpu.bc); }
    case SB_OP_C_FLAG: { return SB_BFE(gb->cpu.af,SB_C_BIT,1)==1; }
    case SB_OP_D: { return SB_U16_HI(gb->cpu.de); }
    case SB_OP_DE: { return gb->cpu.de; }
    case SB_OP_DE_INDIRECT: { return sb_read8(gb,gb->cpu.de); }
    case SB_OP_E: { return SB_U16_LO(gb->cpu.de); }
    case SB_OP_FF00_PLUS_C_INDIRECT: { return sb_read16(gb, 0xff00+SB_U16_LO(gb->cpu.bc)); }
    case SB_OP_FF00_PLUS_U8_INDIRECT: { return sb_read8(gb, 0xff00|sb_read8(gb, gb->cpu.pc-1)); }
    case SB_OP_H: { return SB_U16_HI(gb->cpu.hl); }
    case SB_OP_HL: { return gb->cpu.hl; }
    case SB_OP_HL_DEC_INDIRECT: { return sb_read8(gb,gb->cpu.hl--); }
    case SB_OP_HL_INC_INDIRECT: { return sb_read8(gb,gb->cpu.hl++); }
    case SB_OP_HL_INDIRECT: { return sb_read8(gb,gb->cpu.hl); }
    case SB_OP_I8: { return (int8_t)sb_read8(gb,gb->cpu.pc-1); }
    case SB_OP_L: { return SB_U16_LO(gb->cpu.hl); }
    case SB_OP_NC_FLAG: { return SB_BFE(gb->cpu.af,SB_C_BIT,1)==0; }
    case SB_OP_NONE: { return 0; }
    case SB_OP_NZ_FLAG: { return SB_BFE(gb->cpu.af,SB_Z_BIT,1)==0; }
    case SB_OP_SP: { return gb->cpu.sp; }
    case SB_OP_SP_PLUS_I8: { return gb->cpu.sp+(int8_t)sb_read8(gb,gb->cpu.pc-1); }
    case SB_OP_U16: { return sb_read16(gb, gb->cpu.pc-2); }
    case SB_OP_U16_INDIRECT: { return sb_read16(gb, sb_read16(gb, gb->cpu.pc-2)); }
    case SB_OP_U8: { return sb_read8(gb, gb->cpu.pc-1); }
    case SB_OP_Z_FLAG: { return SB_BFE(gb->cpu.af,SB_Z_BIT,1)==1; }
  }
  printf("Unhandled read operand %d\n",operand);
  return 0;
}

void sb_store_operand(sb_gb_t* gb, int operand, unsigned int value){
  switch(operand){
    case SB_OP_A: { SB_U16_HI_SET(gb->cpu.af,value); return; }
    case SB_OP_AF: { gb->cpu.af = value & 0xfff0; return; }
    case SB_OP_B: { SB_U16_HI_SET(gb->cpu.bc,value);return; }
    case SB_OP_BC: { gb->cpu.bc = value; return; }
    case SB_OP_BC_INDIRECT: { return sb_store8(gb,gb->cpu.bc, value); }
    case SB_OP_C: { SB_U16_LO_SET(gb->cpu.bc,value);return; }
    case SB_OP_D: { SB_U16_HI_SET(gb->cpu.de,value);return; }
    case SB_OP_DE: { gb->cpu.de = value; return; }
    case SB_OP_DE_INDIRECT: { return sb_store8(gb,gb->cpu.de, value); }
    case SB_OP_E: { SB_U16_LO_SET(gb->cpu.de,value);return; }
    case SB_OP_FF00_PLUS_C_INDIRECT: {
      return sb_store8(gb,0xff00+SB_U16_LO(gb->cpu.bc), value);
    }
    case SB_OP_FF00_PLUS_U8_INDIRECT: {
      return sb_store8(gb,0xff00+sb_read8(gb,gb->cpu.pc-1), value);
    }
    case SB_OP_H: { SB_U16_HI_SET(gb->cpu.hl,value);return; }
    case SB_OP_HL: { gb->cpu.hl = value; return; }
    //Increments and decrements happen on the operand read
    case SB_OP_HL_DEC_INDIRECT: { return sb_store8(gb,gb->cpu.hl+1, value); }
    case SB_OP_HL_INC_INDIRECT: { return sb_store8(gb,gb->cpu.hl-1, value); }
    case SB_OP_HL_INDIRECT: { return sb_store8(gb,gb->cpu.hl, value); }
    case SB_OP_L: { SB_U16_LO_SET(gb->cpu.hl,value);return; }
    case SB_OP_SP: { gb->cpu.sp = value; return; }
    case SB_OP_SP_PLUS_I8: { return sb_store8(gb,gb->cpu.sp+(int8_t)sb_read8(gb,gb->cpu.pc-1), value); }
    case SB_OP_U16_INDIRECT: { return sb_store8(gb,sb_read16(gb, gb->cpu.pc-2), value); }

  }
  gb->cpu.trigger_breakpoint=true;
  printf("Unhandled write operand %d\n",operand);
  return;
}
static void sb_push_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask);
static void sb_adc_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int C = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  int r = ((op1&0xff)+(op2&0xff)+C)&0xff;
  //HL calculates half carry as the carry out from bit 11, carry as the carry out from bit 15
  //ADD sp, i8 uses bits 3/7 respectively
  bool carry = ((op1&0xff)+(op2&0xff)+C)>255;
  bool half_carry = ((op1&0xf)+(op2&0xf)+C)>15;
  if(op1_enum==SB_OP_HL){
    carry = ((op1&0xffff)+(op2&0xffff)+C)>65535;
    half_carry = ((op1&0xfff)+(op2&0xfff)+C)>0xfff;
    r = ((op1&0xffff)+(op2&0xffff)+C)&0xffff;
  }
  sb_store_operand(gb,op1_enum, r);
  sb_set_flags(gb, flag_mask, r==0,0,half_carry,carry);
  
}

static void sb_add_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int r = ((op1&0xff)+(op2&0xff))&0xff;
  //HL calculates half carry as the carry out from bit 11, carry as the carry out from bit 15
  //ADD sp, i8 uses bits 3/7 respectively
  bool carry = ((op1&0xff)+(op2&0xff))>255;
  bool zero = (r&0xff) ==0;
  bool half_carry = ((op1&0xf)+(op2&0xf))>15;
  if(op1_enum==SB_OP_HL){
    if((op2&0x80) && op2_enum == SB_OP_I8)op2|=0xff00;
    carry = ((op1&0xffff)+(op2&0xffff))>65535;
    half_carry = ((op1&0xfff)+(op2&0xfff))>0xfff;
    r = ((op1&0xffff)+(op2&0xffff))&0xffff;
  }
  if(op1_enum==SB_OP_SP){
    carry = ((op1&0xff)+(op2&0xff))>0xff;
    half_carry = ((op1&0xf)+(op2&0xf))>0xf;
    r = ((op1&0xffff)+(op2&0xffff))&0xffff;
    zero = false;
  }
  sb_store_operand(gb,op1_enum, r);
  sb_set_flags(gb, flag_mask, zero,0,half_carry,carry);
}

static void sb_and_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int res = SB_U16_HI(gb->cpu.af) & op2 ;
  SB_U16_HI_SET(gb->cpu.af, res );
  bool zero = res==0;
  sb_set_flags(gb, flag_mask, zero,0,1,0);
}

static void sb_bit_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  bool Z = (op2& (1<<op1))==0;
  sb_set_flags(gb, flag_mask, Z,0,1,-1);
}

static void sb_call_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  sb_push_impl(gb,gb->cpu.pc,op2,op1_enum,op2_enum,flag_mask);
  gb->cpu.pc = op1;
}

static void sb_callc_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  if(op1)sb_call_impl(gb, op2, 0, 0, 0, flag_mask);
}

static void sb_ccf_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  unsigned carry = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  sb_set_flags(gb,flag_mask,-1,0,0,!carry);
}

static void sb_cp_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  //HL calculates half carry as the carry out from bit 11, carry as the carry out from bit 15
  //ADD sp, i8 uses bits 3/7 respectively
  bool carry = op1<op2;
  bool zero = op1==op2;
  bool half_carry = (op1&0xf)<(op2&0xf);
  
  sb_set_flags(gb, flag_mask, zero,1,half_carry,carry);
  
}

static void sb_cpl_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int a = SB_U16_HI(gb->cpu.af)^0xff;
  SB_U16_HI_SET(gb->cpu.af, a);
  sb_set_flags(gb, flag_mask, -1,1,1,-1);
}

static void sb_daa_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int a = SB_U16_HI(gb->cpu.af);
  bool H = SB_BFE(gb->cpu.af,SB_H_BIT,1);
  bool C = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  bool N = SB_BFE(gb->cpu.af,SB_N_BIT,1);
  if(N){
    if(C)a-=0x60;
    if(H)a-=0x6;
  }else{
    if(C||a>0x99){a+=0x60;C=true;}
    if(H||(a&0xf)>0x9)a+=0x6;
  }
  SB_U16_HI_SET(gb->cpu.af,a);
  sb_set_flags(gb, flag_mask, (a&0xff)==0,-1,0,C);
}

static void sb_dec_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int r = op1-1;
  sb_set_flags(gb, flag_mask, (r&0xff)==0,1,((op1&0xf)-1)<0,-1);
  sb_store_operand(gb,op1_enum, r);
}

static void sb_di_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  gb->cpu.interrupt_enable = false;
  gb->cpu.deferred_interrupt_enable = false;
}

static void sb_ei_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  gb->cpu.deferred_interrupt_enable = true;
}

static void sb_halt_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  gb->cpu.wait_for_interrupt=gb->cpu.interrupt_enable;
}

static void sb_inc_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int r = op1+1;
  sb_set_flags(gb,flag_mask, (r&0xff)==0,0,((op1&0xf)+1)>0xf,-1);
  sb_store_operand(gb,op1_enum, r);
}

static void sb_jp_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  gb->cpu.pc = op1;
}

static void sb_jpc_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  if(op1)sb_jp_impl(gb, op2, 0, 0, 0, flag_mask);
}

static void sb_jr_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  gb->cpu.pc += (int8_t)op1;
}

static void sb_jrc_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  if(op1) sb_jr_impl(gb, op2, 0, 0, 0, flag_mask);
}

static void sb_ld_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  if(op1_enum == SB_OP_U16_INDIRECT && op2_enum==SB_OP_SP){
    sb_store16(gb, sb_read16(gb, gb->cpu.pc-2), op2);
  }else if(op1_enum == SB_OP_HL && op2_enum==SB_OP_SP_PLUS_I8){
    sb_store_operand(gb,op1_enum, op2);
    op1 = gb->cpu.sp;
    op2 = (int8_t)sb_read8(gb, gb->cpu.pc-1);
    bool carry = ((op1&0xff)+(op2&0xff))>0xff;
    bool half_carry = ((op1&0xf)+(op2&0xf))>0xf;
    
    sb_set_flags(gb, flag_mask, 0,0,half_carry,carry);
  }else sb_store_operand(gb,op1_enum,op2);
}

static void sb_nop_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
}

static void sb_nop_no_instr_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  //This instruction should never be called, break if it does
  gb->cpu.trigger_breakpoint=true;
  printf("NOP_NO_INSTR executed\n");
}

static void sb_or_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int r = SB_U16_HI(gb->cpu.af) | op2;
  SB_U16_HI_SET(gb->cpu.af, r);
  bool zero = r==0;
  sb_set_flags(gb, flag_mask, zero,0,0,0);
}

static void sb_pop_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  sb_store_operand(gb,op1_enum,sb_read16(gb,gb->cpu.sp));
  gb->cpu.sp+=2;
}

static void sb_prefix_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  gb->cpu.prefix_op = true;
}

static void sb_push_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  gb->cpu.sp-=2;
  sb_store16(gb,gb->cpu.sp,op1);
}

static void sb_res_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int r = op2& (~(1<<op1));
  sb_store_operand(gb,op2_enum,r);
}

static void sb_ret_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  gb->cpu.pc=sb_read16(gb,gb->cpu.sp);
  gb->cpu.sp+=2;
}

static void sb_retc_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  if(op1)sb_ret_impl(gb, op2, 0, 0, 0,flag_mask);
}

static void sb_reti_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  sb_ret_impl(gb,op1,op2,op1_enum,op2_enum,flag_mask);
  sb_ei_impl(gb,op1,op2,op1_enum,op2_enum,flag_mask);
}

static void sb_rl_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  unsigned carry = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  unsigned int carry_out = SB_BFE(op1,7,1);
  op1 = (op1<<1)|(carry);
  sb_store_operand(gb,op1_enum,op1);
  sb_set_flags(gb, flag_mask, (op1&0xff)==0,0,0,carry_out);
}

static void sb_rla_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  op1 = SB_U16_HI(gb->cpu.af);
  unsigned carry = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  unsigned int carry_out = SB_BFE(op1,7,1);
  op1 = (op1<<1)|(carry);
  SB_U16_HI_SET(gb->cpu.af,op1);
  sb_set_flags(gb, flag_mask, 0,0,0,carry_out);
}

static void sb_rlc_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  unsigned carry = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  unsigned int carry_out = SB_BFE(op1,7,1);
  op1 = (op1<<1)|(carry_out);
  sb_store_operand(gb,op1_enum,op1);
  sb_set_flags(gb, flag_mask, (op1&0xff)==0,0,0,carry_out);
}

static void sb_rlca_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  op1 = SB_U16_HI(gb->cpu.af);
  unsigned carry = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  unsigned int carry_out = SB_BFE(op1,7,1);
  op1 = (op1<<1)|(carry_out);
  SB_U16_HI_SET(gb->cpu.af,op1);
  sb_set_flags(gb, flag_mask, 0,0,0,carry_out);
}

static void sb_rr_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  unsigned carry = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  unsigned int carry_out = op1&1;
  op1 = (op1>>1)|(carry<<7);
  sb_store_operand(gb,op1_enum,op1);
  sb_set_flags(gb, flag_mask, (op1&0xff)==0,0,0,carry_out);
  
}

static void sb_rra_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  unsigned int a = SB_U16_HI(gb->cpu.af);
  unsigned carry = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  unsigned int carry_out = a&1;
  a = (a>>1)|(carry<<7);
  SB_U16_HI_SET(gb->cpu.af,a);
  sb_set_flags(gb, flag_mask, 0,0,0,carry_out);
}

static void sb_rrc_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  unsigned carry = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  unsigned int carry_out = SB_BFE(op1,0,1);
  op1 = (op1>>1)|(carry_out<<7);
  sb_set_flags(gb, flag_mask, (op1&0xff)==0,0,0,carry_out);
  sb_store_operand(gb,op1_enum,op1);
}

static void sb_rrca_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  op1 = SB_U16_HI(gb->cpu.af);
  unsigned carry = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  unsigned int carry_out = SB_BFE(op1,0,1);
  op1 = (op1>>1)|(carry_out<<7);
  sb_set_flags(gb, flag_mask, 0,0,0,carry_out);
  SB_U16_HI_SET(gb->cpu.af,op1);
}

static void sb_rst_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  sb_call_impl(gb,op1,op2,op1_enum,op2_enum,flag_mask);
}

static void sb_sbc_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int C = SB_BFE(gb->cpu.af,SB_C_BIT,1);
  int r = ((op1&0xff)-(op2&0xff)-C)&0xff;
  //HL calculates half carry as the carry out from bit 11, carry as the carry out from bit 15
  //ADD sp, i8 uses bits 3/7 respectively
  bool carry = ((op1&0xff)-(op2&0xff)-C)<0;
  bool half_carry = ((op1&0xf)-(op2&0xf)-C)<0;
  if(op1_enum==SB_OP_HL){
    carry = ((op1&0xffff)-(op2&0xffff)-C)<0;
    half_carry = ((op1&0xfff)+(op2&0xfff)-C)<0;
    r = ((op1&0xffff)-(op2&0xffff)-C)&0xffff;
  }
  sb_store_operand(gb,op1_enum, r);
  sb_set_flags(gb, flag_mask,r==0,1,half_carry,carry);}

static void sb_scf_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  sb_set_flags(gb,flag_mask,-1,0,0,1);
}

static void sb_set_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int r = op2| (1<<op1);
  sb_store_operand(gb,op2_enum,r);
}

static void sb_sla_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  unsigned int carry_out = SB_BFE(op1,7,1);
  op1 = (op1<<1);
  sb_store_operand(gb,op1_enum,op1);
  sb_set_flags(gb, flag_mask, (op1&0xff) ==0,0,0,carry_out);
}

static void sb_sra_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  unsigned int carry_out = op1&1;
  op1 = (op1>>1)|(op1&0x80);
  sb_store_operand(gb,op1_enum,op1);
  sb_set_flags(gb, flag_mask, (op1&0xff) ==0,0,0,carry_out);
}

static void sb_srl_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  // See: http://www.devrs.com/gb/files/opcodes.html
  unsigned int carry_out = op1&1;
  op1 = (op1>>1);
  sb_store_operand(gb,op1_enum,op1);
  sb_set_flags(gb, flag_mask, (op1&0xff) ==0,0,0,carry_out);
}

static void sb_stop_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  gb->cpu.wait_for_interrupt=true;
  gb->cpu.interrupt_enable = true; 
  // Div is reset on stop
  gb->timers.clocks_till_div_inc = 0;
  sb_store8(gb,0xff04,0);
}

static void sb_sub_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int r = ((op1&0xff)-(op2&0xff))&0xff;
  //HL calculates half carry as the carry out from bit 11, carry as the carry out from bit 15
  //ADD sp, i8 uses bits 3/7 respectively
  bool carry = ((op1&0xff)-(op2&0xff))<0;
  bool zero = (r&0xff) ==0;
  bool half_carry = ((op1&0xf)-(op2&0xf))<0;
  if(op1_enum==SB_OP_HL){
    carry = ((op1&0xffff)-(op2&0xffff))<0;
    half_carry = ((op1&0xfff)-(op2&0xfff))<0;
    r = ((op1&0xffff)-(op2&0xffff))&0xffff;
  }
  sb_store_operand(gb,op1_enum, r);
  sb_set_flags(gb, flag_mask, zero,1,half_carry,carry);
  
}

static void sb_swap_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  int r = ((op1&0xf)<<4)|((op1&0xf0)>>4);
  bool zero = (r&0xff) ==0;
  sb_store_operand(gb,op1_enum, r);
  sb_set_flags(gb, flag_mask, zero,0,0,0);
  
}

static void sb_xor_impl(sb_gb_t* gb, int op1, int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask){
  unsigned res = ((SB_U16_HI(gb->cpu.af)) ^op2)&0xff;
  bool zero = (res&0xff)==0;
  sb_set_flags(gb, flag_mask, zero,0,0,0);
  sb_store_operand(gb,op1_enum, res);
}

#endif