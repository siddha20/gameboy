#include "cpu.h"

namespace emulator
{
void CPU::opcode_00() { /* no op */ }
void CPU::opcode_01() { ld_16_imd16(registers.bc); }
void CPU::opcode_02() { mapper.write(a, registers.bc.word); }
void CPU::opcode_03() { ++registers.bc.word; }
void CPU::opcode_04() { inc_8(b); }
void CPU::opcode_05() { dec_8(b); }
void CPU::opcode_06() { ld_8_imd8(b); }
void CPU::opcode_07() { rot<0, 0, -1>(a); }
void CPU::opcode_08() { ld_16_addr16_from(stack_pointer); }
void CPU::opcode_09() { add_16(registers.hl, registers.bc); }
void CPU::opcode_0a() { a = mapper.read(registers.bc.word); }
void CPU::opcode_0b() { --registers.bc.word; }
void CPU::opcode_0c() { inc_8(c); }
void CPU::opcode_0d() { dec_8(c); }
void CPU::opcode_0e() { ld_8_imd8(c); }
void CPU::opcode_0f() { rot<0, 0, 1>(a); }
void CPU::opcode_10() { stop(); }
void CPU::opcode_11() { ld_16_imd16(registers.de); }
void CPU::opcode_12() { mapper.write(a, registers.de.word); }
void CPU::opcode_13() { ++registers.de.word; }
void CPU::opcode_14() { inc_8(d); }
void CPU::opcode_15() { dec_8(d); }
void CPU::opcode_16() { ld_8_imd8(d); }
void CPU::opcode_17() { rot<0, 1, -1>(a); }
void CPU::opcode_18() { jump_imds8(true); }
void CPU::opcode_19() { add_16(registers.hl, registers.de); }
void CPU::opcode_1a() { a = mapper.read(registers.de.word); }
void CPU::opcode_1b() { --registers.de.word; }
void CPU::opcode_1c() { inc_8(e); }
void CPU::opcode_1d() { dec_8(e); }
void CPU::opcode_1e() { ld_8_imd8(e); }
void CPU::opcode_1f() { rot<0, 1, 1>(a);}
void CPU::opcode_20() { jump_imds8(!registers.af.lo.zero_flag); }
void CPU::opcode_21() { ld_16_imd16(registers.hl); }
void CPU::opcode_22() { mapper.write(a, registers.hl.word++); }
void CPU::opcode_23() { ++registers.hl.word; }
void CPU::opcode_24() { inc_8(h); }
void CPU::opcode_25() { dec_8(h); }
void CPU::opcode_26() { ld_8_imd8(h); }
void CPU::opcode_27() { daa(); }
void CPU::opcode_28() { jump_imds8(registers.af.lo.zero_flag); }
void CPU::opcode_29() { add_16(registers.hl, registers.hl); }
void CPU::opcode_2a() { a = mapper.read(registers.hl.word++); }
void CPU::opcode_2b() { --registers.hl.word; }
void CPU::opcode_2c() { inc_8(l); }
void CPU::opcode_2d() { dec_8(l); }
void CPU::opcode_2e() { ld_8_imd8(l); }
void CPU::opcode_2f() { cpl(); }
void CPU::opcode_30() { jump_imds8(!registers.af.lo.carry_flag); }
void CPU::opcode_31() { ld_16_imd16(stack_pointer); }
void CPU::opcode_32() { mapper.write(a, registers.hl.word--); }
void CPU::opcode_33() { ++stack_pointer.word; }
void CPU::opcode_34() { inc_8_ind(registers.hl); }
void CPU::opcode_35() { dec_8_ind(registers.hl); }
void CPU::opcode_36() { ld_8_imd8_ind(registers.hl); }
void CPU::opcode_37() { scf(); }
void CPU::opcode_38() { jump_imds8(registers.af.lo.carry_flag); }
void CPU::opcode_39() { add_16(registers.hl, stack_pointer); }
void CPU::opcode_3a() { a = mapper.read(registers.hl.word--); }
void CPU::opcode_3b() { --stack_pointer.word; }
void CPU::opcode_3c() { inc_8(a); }
void CPU::opcode_3d() { dec_8(a); }
void CPU::opcode_3e() { ld_8_imd8(a); }
void CPU::opcode_3f() { ccf(); }
void CPU::opcode_40() { b = b; }
void CPU::opcode_41() { b = c; }
void CPU::opcode_42() { b = d; }
void CPU::opcode_43() { b = e; }
void CPU::opcode_44() { b = h; }
void CPU::opcode_45() { b = l; }
void CPU::opcode_46() { b = mapper.read(registers.hl.word); }
void CPU::opcode_47() { b = a; }
void CPU::opcode_48() { c = b; }
void CPU::opcode_49() { c = c; }
void CPU::opcode_4a() { c = d; }
void CPU::opcode_4b() { c = e; }
void CPU::opcode_4c() { c = h; }
void CPU::opcode_4d() { c = l; }
void CPU::opcode_4e() { c = mapper.read(registers.hl.word); }
void CPU::opcode_4f() { c = a; }
void CPU::opcode_50() { d = b; }
void CPU::opcode_51() { d = c; }
void CPU::opcode_52() { d = d; }
void CPU::opcode_53() { d = e; }
void CPU::opcode_54() { d = h; }
void CPU::opcode_55() { d = l; }
void CPU::opcode_56() { d = mapper.read(registers.hl.word); }
void CPU::opcode_57() { d = a; }
void CPU::opcode_58() { e = b;}
void CPU::opcode_59() { e = c; }
void CPU::opcode_5a() { e = d; }
void CPU::opcode_5b() { e = e; }
void CPU::opcode_5c() { e = h; }
void CPU::opcode_5d() { e = l; }
void CPU::opcode_5e() { e = mapper.read(registers.hl.word); }
void CPU::opcode_5f() { e = a; }
void CPU::opcode_60() { h = b; }
void CPU::opcode_61() { h = c; }
void CPU::opcode_62() { h = d; }
void CPU::opcode_63() { h = e; }
void CPU::opcode_64() { h = h; }
void CPU::opcode_65() { h = l; }
void CPU::opcode_66() { h = mapper.read(registers.hl.word); }
void CPU::opcode_67() { h = a; }
void CPU::opcode_68() { l = b; }
void CPU::opcode_69() { l = c; }
void CPU::opcode_6a() { l = d; }
void CPU::opcode_6b() { l = e; }
void CPU::opcode_6c() { l = h; }
void CPU::opcode_6d() { l = l; }
void CPU::opcode_6e() { l = mapper.read(registers.hl.word); }
void CPU::opcode_6f() { l = a; }
void CPU::opcode_70() { mapper.write(b, registers.hl.word); }
void CPU::opcode_71() { mapper.write(c, registers.hl.word); }
void CPU::opcode_72() { mapper.write(d, registers.hl.word); }
void CPU::opcode_73() { mapper.write(e, registers.hl.word); }
void CPU::opcode_74() { mapper.write(h, registers.hl.word); }
void CPU::opcode_75() { mapper.write(l, registers.hl.word); }
void CPU::opcode_76() { halt(); } 
void CPU::opcode_77() { mapper.write(a, registers.hl.word); }
void CPU::opcode_78() { a = b; }
void CPU::opcode_79() { a = c;}
void CPU::opcode_7a() { a = d; }
void CPU::opcode_7b() { a = e; }
void CPU::opcode_7c() { a = h; }
void CPU::opcode_7d() { a = l; }
void CPU::opcode_7e() { a = mapper.read(registers.hl.word); }
void CPU::opcode_7f() { a = a; }
void CPU::opcode_80() { add(a, b); }
void CPU::opcode_81() { add(a, c); }
void CPU::opcode_82() { add(a, d); }
void CPU::opcode_83() { add(a, e); }
void CPU::opcode_84() { add(a, h); }
void CPU::opcode_85() { add(a, l); }
void CPU::opcode_86() { add(a, mapper.read(registers.hl.word)); }
void CPU::opcode_87() { add(a, a); }
void CPU::opcode_88() { adc(a, b); }
void CPU::opcode_89() { adc(a, c); }
void CPU::opcode_8a() { adc(a, d); }
void CPU::opcode_8b() { adc(a, e); }
void CPU::opcode_8c() { adc(a, h); }
void CPU::opcode_8d() { adc(a, l); }
void CPU::opcode_8e() { adc(a, mapper.read(registers.hl.word)); }
void CPU::opcode_8f() { adc(a, a); }
void CPU::opcode_90() { sub(a, b); }
void CPU::opcode_91() { sub(a, c); }
void CPU::opcode_92() { sub(a, d); }
void CPU::opcode_93() { sub(a, e); }
void CPU::opcode_94() { sub(a, h); }
void CPU::opcode_95() { sub(a, l); }
void CPU::opcode_96() { sub(a, mapper.read(registers.hl.word)); }
void CPU::opcode_97() { sub(a, a); }
void CPU::opcode_98() { sbc(a, b); }
void CPU::opcode_99() { sbc(a, c); }
void CPU::opcode_9a() { sbc(a, d); }
void CPU::opcode_9b() { sbc(a, e); }
void CPU::opcode_9c() { sbc(a, h); }
void CPU::opcode_9d() { sbc(a, l); }
void CPU::opcode_9e() { sbc(a, mapper.read(registers.hl.word)); }
void CPU::opcode_9f() { sbc(a, a); }
void CPU::opcode_a0() { m_and(a, b); }
void CPU::opcode_a1() { m_and(a, c); }
void CPU::opcode_a2() { m_and(a, d); }
void CPU::opcode_a3() { m_and(a, e); }
void CPU::opcode_a4() { m_and(a, h); }
void CPU::opcode_a5() { m_and(a, l); }
void CPU::opcode_a6() { m_and(a, mapper.read(registers.hl.word)); }
void CPU::opcode_a7() { m_and(a, a); }
void CPU::opcode_a8() { m_xor(a, b); }
void CPU::opcode_a9() { m_xor(a, c); }
void CPU::opcode_aa() { m_xor(a, d); }
void CPU::opcode_ab() { m_xor(a, e); }
void CPU::opcode_ac() { m_xor(a, h); }
void CPU::opcode_ad() { m_xor(a, l); }
void CPU::opcode_ae() { m_xor(a, mapper.read(registers.hl.word)); }
void CPU::opcode_af() { m_xor(a, a); }
void CPU::opcode_b0() { m_or(a, b); }
void CPU::opcode_b1() { m_or(a, c); }
void CPU::opcode_b2() { m_or(a, d); }
void CPU::opcode_b3() { m_or(a, e); }
void CPU::opcode_b4() { m_or(a, h); }
void CPU::opcode_b5() { m_or(a, l); }
void CPU::opcode_b6() { m_or(a, mapper.read(registers.hl.word)); }
void CPU::opcode_b7() { m_or(a, a); }
void CPU::opcode_b8() { m_cp(a, b); }
void CPU::opcode_b9() { m_cp(a, c); }
void CPU::opcode_ba() { m_cp(a, d); }
void CPU::opcode_bb() { m_cp(a, e); }
void CPU::opcode_bc() { m_cp(a, h); }
void CPU::opcode_bd() { m_cp(a, l); }
void CPU::opcode_be() { m_cp(a, mapper.read(registers.hl.word)); }
void CPU::opcode_bf() { m_cp(a, a); }
void CPU::opcode_c0() { ret<0>(!registers.af.lo.zero_flag); }
void CPU::opcode_c1() { pop(registers.bc); }
void CPU::opcode_c2() { jump_addr16(!registers.af.lo.zero_flag); }
void CPU::opcode_c3() { jump_addr16(true); }
void CPU::opcode_c4() { call_addr16(!registers.af.lo.zero_flag); }
void CPU::opcode_c5() { push(registers.bc); }
void CPU::opcode_c6() { add_imd8(a); }
void CPU::opcode_c7() { call(0x0000); }
void CPU::opcode_c8() { ret<0>(registers.af.lo.zero_flag); }
void CPU::opcode_c9() { ret<0>(true); }
void CPU::opcode_ca() { jump_addr16(registers.af.lo.zero_flag); }
void CPU::opcode_cb() { cb(); }
void CPU::opcode_cc() { call_addr16(registers.af.lo.zero_flag); }
void CPU::opcode_cd() { call_addr16(true); }
void CPU::opcode_ce() { adc_imd8(a); }
void CPU::opcode_cf() { call(0x0008); }
void CPU::opcode_d0() { ret<0>(!registers.af.lo.carry_flag); }
void CPU::opcode_d1() { pop(registers.de); }
void CPU::opcode_d2() { jump_addr16(!registers.af.lo.carry_flag); }
void CPU::opcode_d3() { /* no instruction */ }
void CPU::opcode_d4() { call_addr16(!registers.af.lo.carry_flag); }
void CPU::opcode_d5() { push(registers.de); }
void CPU::opcode_d6() { sub_imd8(a); }
void CPU::opcode_d7() { call(0x0010); }
void CPU::opcode_d8() { ret<0>(registers.af.lo.carry_flag); }
void CPU::opcode_d9() { ret<1>(true); }
void CPU::opcode_da() { jump_addr16(registers.af.lo.carry_flag); }
void CPU::opcode_db() { /* no instruction */ }
void CPU::opcode_dc() { call_addr16(registers.af.lo.carry_flag); }
void CPU::opcode_dd() { /* no instruction */ }
void CPU::opcode_de() { sbc_imd8(a); }
void CPU::opcode_df() { call(0x0018); }
void CPU::opcode_e0() { ldh_8_addr16_from(a); }
void CPU::opcode_e1() { pop(registers.hl); }
void CPU::opcode_e2() { mapper.write(a, 0xFF00 + c); }
void CPU::opcode_e3() { /* no instruction */ }
void CPU::opcode_e4() { /* no instruction */ }
void CPU::opcode_e5() { push(registers.hl); }
void CPU::opcode_e6() { m_and_imd8(a); }
void CPU::opcode_e7() { call(0x0020); }
void CPU::opcode_e8() { add_16_imds8(stack_pointer); }
void CPU::opcode_e9() { program_counter.word = registers.hl.word; }
void CPU::opcode_ea() { ld_8_addr16_from(a); }
void CPU::opcode_eb() { /* no instruction */ }
void CPU::opcode_ec() { /* no instruction */ }
void CPU::opcode_ed() { /* no instruction */ }
void CPU::opcode_ee() { m_xor_imd8(a); }
void CPU::opcode_ef() { call(0x0028); }
void CPU::opcode_f0() { ldh_8_addr16(a); }
void CPU::opcode_f1() { pop(registers.af); }
void CPU::opcode_f2() { a = mapper.read(0xFF00 + c); }
void CPU::opcode_f3() { mapper.memory.interrupts.IME = 0; }
void CPU::opcode_f4() { /* no instruction */ }
void CPU::opcode_f5() { push(registers.af); }
void CPU::opcode_f6() { m_or_imd8(a); }
void CPU::opcode_f7() { call(0x0030); }
void CPU::opcode_f8() { ldhl(); }
void CPU::opcode_f9() { stack_pointer.word = registers.hl.word; }
void CPU::opcode_fa() { ld_8_addr16(a); }
void CPU::opcode_fb() { mapper.memory.interrupts.IME = 1; }
void CPU::opcode_fc() { /* no instruction */ }
void CPU::opcode_fd() { /* no instruction */ }
void CPU::opcode_fe() { m_cp_imd8(a); }
void CPU::opcode_ff() { call(0x0038); }

void CPU::opcode_cb_00() { rot<1, 0, -1>(b); }
void CPU::opcode_cb_01() { rot<1, 0, -1>(c); }
void CPU::opcode_cb_02() { rot<1, 0, -1>(d); }
void CPU::opcode_cb_03() { rot<1, 0, -1>(e); }
void CPU::opcode_cb_04() { rot<1, 0, -1>(h); }
void CPU::opcode_cb_05() { rot<1, 0, -1>(l); }
void CPU::opcode_cb_06() { rot_hl<0, -1>(); }
void CPU::opcode_cb_07() { rot<1, 0, -1>(a); }
void CPU::opcode_cb_08() { rot<1, 0, 1>(b); }
void CPU::opcode_cb_09() { rot<1, 0, 1>(c); }
void CPU::opcode_cb_0a() { rot<1, 0, 1>(d); }
void CPU::opcode_cb_0b() { rot<1, 0, 1>(e); }
void CPU::opcode_cb_0c() { rot<1, 0, 1>(h); }
void CPU::opcode_cb_0d() { rot<1, 0, 1>(l); }
void CPU::opcode_cb_0e() { rot_hl<0, 1>(); }
void CPU::opcode_cb_0f() { rot<1, 0, 1>(a); }
void CPU::opcode_cb_10() { rot<1, 1, -1>(b); }
void CPU::opcode_cb_11() { rot<1, 1, -1>(c); }
void CPU::opcode_cb_12() { rot<1, 1, -1>(d); }
void CPU::opcode_cb_13() { rot<1, 1, -1>(e); }
void CPU::opcode_cb_14() { rot<1, 1, -1>(h); }
void CPU::opcode_cb_15() { rot<1, 1, -1>(l); }
void CPU::opcode_cb_16() { rot_hl<1, -1>(); }
void CPU::opcode_cb_17() { rot<1, 1, -1>(a); }
void CPU::opcode_cb_18() { rot<1, 1, 1>(b); }
void CPU::opcode_cb_19() { rot<1, 1, 1>(c); }
void CPU::opcode_cb_1a() { rot<1, 1, 1>(d); }
void CPU::opcode_cb_1b() { rot<1, 1, 1>(e); }
void CPU::opcode_cb_1c() { rot<1, 1, 1>(h); }
void CPU::opcode_cb_1d() { rot<1, 1, 1>(l); }
void CPU::opcode_cb_1e() { rot_hl<1, 1>(); }
void CPU::opcode_cb_1f() { rot<1, 1, 1>(a); }
void CPU::opcode_cb_20() { sla(b); }
void CPU::opcode_cb_21() { sla(c); }
void CPU::opcode_cb_22() { sla(d); }
void CPU::opcode_cb_23() { sla(e); }
void CPU::opcode_cb_24() { sla(h); }
void CPU::opcode_cb_25() { sla(l); }
void CPU::opcode_cb_26() { sla_hl(); }
void CPU::opcode_cb_27() { sla(a); }
void CPU::opcode_cb_28() { sr<0>(b); }
void CPU::opcode_cb_29() { sr<0>(c); }
void CPU::opcode_cb_2a() { sr<0>(d); }
void CPU::opcode_cb_2b() { sr<0>(e); }
void CPU::opcode_cb_2c() { sr<0>(h); }
void CPU::opcode_cb_2d() { sr<0>(l); }
void CPU::opcode_cb_2e() { sr_hl<0>(); }
void CPU::opcode_cb_2f() { sr<0>(a); }
void CPU::opcode_cb_30() { swap(b); }
void CPU::opcode_cb_31() { swap(c); }
void CPU::opcode_cb_32() { swap(d); }
void CPU::opcode_cb_33() { swap(e); }
void CPU::opcode_cb_34() { swap(h); }
void CPU::opcode_cb_35() { swap(l); }
void CPU::opcode_cb_36() { swap_hl(); }
void CPU::opcode_cb_37() { swap(a); }
void CPU::opcode_cb_38() { sr<1>(b); }
void CPU::opcode_cb_39() { sr<1>(c); }
void CPU::opcode_cb_3a() { sr<1>(d); }
void CPU::opcode_cb_3b() { sr<1>(e); }
void CPU::opcode_cb_3c() { sr<1>(h); }
void CPU::opcode_cb_3d() { sr<1>(l); }
void CPU::opcode_cb_3e() { sr_hl<1>(); }
void CPU::opcode_cb_3f() { sr<1>(a); }
void CPU::opcode_cb_40() { test_bit(b, 0); }
void CPU::opcode_cb_41() { test_bit(c, 0); }
void CPU::opcode_cb_42() { test_bit(d, 0); }
void CPU::opcode_cb_43() { test_bit(e, 0); }
void CPU::opcode_cb_44() { test_bit(h, 0); }
void CPU::opcode_cb_45() { test_bit(l, 0); }
void CPU::opcode_cb_46() { test_bit(mapper.read(registers.hl.word), 0); }
void CPU::opcode_cb_47() { test_bit(a, 0); }
void CPU::opcode_cb_48() { test_bit(b, 1); }
void CPU::opcode_cb_49() { test_bit(c, 1); }
void CPU::opcode_cb_4a() { test_bit(d, 1); }
void CPU::opcode_cb_4b() { test_bit(e, 1); }
void CPU::opcode_cb_4c() { test_bit(h, 1); }
void CPU::opcode_cb_4d() { test_bit(l, 1); }
void CPU::opcode_cb_4e() { test_bit(mapper.read(registers.hl.word), 1); }
void CPU::opcode_cb_4f() { test_bit(a, 1); }
void CPU::opcode_cb_50() { test_bit(b, 2); }
void CPU::opcode_cb_51() { test_bit(c, 2); }
void CPU::opcode_cb_52() { test_bit(d, 2); }
void CPU::opcode_cb_53() { test_bit(e, 2); }
void CPU::opcode_cb_54() { test_bit(h, 2); }
void CPU::opcode_cb_55() { test_bit(l, 2); }
void CPU::opcode_cb_56() { test_bit(mapper.read(registers.hl.word), 2); }
void CPU::opcode_cb_57() { test_bit(a, 2); }
void CPU::opcode_cb_58() { test_bit(b, 3); }
void CPU::opcode_cb_59() { test_bit(c, 3); }
void CPU::opcode_cb_5a() { test_bit(d, 3); }
void CPU::opcode_cb_5b() { test_bit(e, 3); }
void CPU::opcode_cb_5c() { test_bit(h, 3); }
void CPU::opcode_cb_5d() { test_bit(l, 3); }
void CPU::opcode_cb_5e() { test_bit(mapper.read(registers.hl.word), 3); }
void CPU::opcode_cb_5f() { test_bit(a, 3); }
void CPU::opcode_cb_60() { test_bit(b, 4); }
void CPU::opcode_cb_61() { test_bit(c, 4); }
void CPU::opcode_cb_62() { test_bit(d, 4); }
void CPU::opcode_cb_63() { test_bit(e, 4); }
void CPU::opcode_cb_64() { test_bit(h, 4); }
void CPU::opcode_cb_65() { test_bit(l, 4); }
void CPU::opcode_cb_66() { test_bit(mapper.read(registers.hl.word), 4); }
void CPU::opcode_cb_67() { test_bit(a, 4); }
void CPU::opcode_cb_68() { test_bit(b, 5); }
void CPU::opcode_cb_69() { test_bit(c, 5); }
void CPU::opcode_cb_6a() { test_bit(d, 5); }
void CPU::opcode_cb_6b() { test_bit(e, 5); }
void CPU::opcode_cb_6c() { test_bit(h, 5); }
void CPU::opcode_cb_6d() { test_bit(l, 5); }
void CPU::opcode_cb_6e() { test_bit(mapper.read(registers.hl.word), 5); }
void CPU::opcode_cb_6f() { test_bit(a, 5); }
void CPU::opcode_cb_70() { test_bit(b, 6); }
void CPU::opcode_cb_71() { test_bit(c, 6); }
void CPU::opcode_cb_72() { test_bit(d, 6); }
void CPU::opcode_cb_73() { test_bit(e, 6); }
void CPU::opcode_cb_74() { test_bit(h, 6); }
void CPU::opcode_cb_75() { test_bit(l, 6); }
void CPU::opcode_cb_76() { test_bit(mapper.read(registers.hl.word), 6); }
void CPU::opcode_cb_77() { test_bit(a, 6); }
void CPU::opcode_cb_78() { test_bit(b, 7); }
void CPU::opcode_cb_79() { test_bit(c, 7); }
void CPU::opcode_cb_7a() { test_bit(d, 7); }
void CPU::opcode_cb_7b() { test_bit(e, 7); }
void CPU::opcode_cb_7c() { test_bit(h, 7); }
void CPU::opcode_cb_7d() { test_bit(l, 7); }
void CPU::opcode_cb_7e() { test_bit(mapper.read(registers.hl.word), 7); }
void CPU::opcode_cb_7f() { test_bit(a, 7); }
void CPU::opcode_cb_80() { set_bit(b, 0, 0); }
void CPU::opcode_cb_81() { set_bit(c, 0, 0); }
void CPU::opcode_cb_82() { set_bit(d, 0, 0); }
void CPU::opcode_cb_83() { set_bit(e, 0, 0); }
void CPU::opcode_cb_84() { set_bit(h, 0, 0); }
void CPU::opcode_cb_85() { set_bit(l, 0, 0); }
void CPU::opcode_cb_86() { set_bit_hl(0, 0); }
void CPU::opcode_cb_87() { set_bit(a, 0, 0); }
void CPU::opcode_cb_88() { set_bit(b, 1, 0); }
void CPU::opcode_cb_89() { set_bit(c, 1, 0); }
void CPU::opcode_cb_8a() { set_bit(d, 1, 0); }
void CPU::opcode_cb_8b() { set_bit(e, 1, 0); }
void CPU::opcode_cb_8c() { set_bit(h, 1, 0); }
void CPU::opcode_cb_8d() { set_bit(l, 1, 0); }
void CPU::opcode_cb_8e() { set_bit_hl(1, 0); }
void CPU::opcode_cb_8f() { set_bit(a, 1, 0); }
void CPU::opcode_cb_90() { set_bit(b, 2, 0); }
void CPU::opcode_cb_91() { set_bit(c, 2, 0); }
void CPU::opcode_cb_92() { set_bit(d, 2, 0); }
void CPU::opcode_cb_93() { set_bit(e, 2, 0); }
void CPU::opcode_cb_94() { set_bit(h, 2, 0); }
void CPU::opcode_cb_95() { set_bit(l, 2, 0); }
void CPU::opcode_cb_96() { set_bit_hl(2, 0); }
void CPU::opcode_cb_97() { set_bit(a, 2, 0); }
void CPU::opcode_cb_98() { set_bit(b, 3, 0); }
void CPU::opcode_cb_99() { set_bit(c, 3, 0); }
void CPU::opcode_cb_9a() { set_bit(d, 3, 0); }
void CPU::opcode_cb_9b() { set_bit(e, 3, 0); }
void CPU::opcode_cb_9c() { set_bit(h, 3, 0); }
void CPU::opcode_cb_9d() { set_bit(l, 3, 0); }
void CPU::opcode_cb_9e() { set_bit_hl(3, 0); }
void CPU::opcode_cb_9f() { set_bit(a, 3, 0); }
void CPU::opcode_cb_a0() { set_bit(b, 4, 0); }
void CPU::opcode_cb_a1() { set_bit(c, 4, 0); }
void CPU::opcode_cb_a2() { set_bit(d, 4, 0); }
void CPU::opcode_cb_a3() { set_bit(e, 4, 0); }
void CPU::opcode_cb_a4() { set_bit(h, 4, 0); }
void CPU::opcode_cb_a5() { set_bit(l, 4, 0); }
void CPU::opcode_cb_a6() { set_bit_hl(4, 0); }
void CPU::opcode_cb_a7() { set_bit(a, 4, 0); }
void CPU::opcode_cb_a8() { set_bit(b, 5, 0); }
void CPU::opcode_cb_a9() { set_bit(c, 5, 0); }
void CPU::opcode_cb_aa() { set_bit(d, 5, 0); }
void CPU::opcode_cb_ab() { set_bit(e, 5, 0); }
void CPU::opcode_cb_ac() { set_bit(h, 5, 0); }
void CPU::opcode_cb_ad() { set_bit(l, 5, 0); }
void CPU::opcode_cb_ae() { set_bit_hl(5, 0); }
void CPU::opcode_cb_af() { set_bit(a, 5, 0); }
void CPU::opcode_cb_b0() { set_bit(b, 6, 0); }
void CPU::opcode_cb_b1() { set_bit(c, 6, 0); }
void CPU::opcode_cb_b2() { set_bit(d, 6, 0); }
void CPU::opcode_cb_b3() { set_bit(e, 6, 0); }
void CPU::opcode_cb_b4() { set_bit(h, 6, 0); }
void CPU::opcode_cb_b5() { set_bit(l, 6, 0); }
void CPU::opcode_cb_b6() { set_bit_hl(6, 0); }
void CPU::opcode_cb_b7() { set_bit(a, 6, 0); }
void CPU::opcode_cb_b8() { set_bit(b, 7, 0); }
void CPU::opcode_cb_b9() { set_bit(c, 7, 0); }
void CPU::opcode_cb_ba() { set_bit(d, 7, 0); }
void CPU::opcode_cb_bb() { set_bit(e, 7, 0); }
void CPU::opcode_cb_bc() { set_bit(h, 7, 0); }
void CPU::opcode_cb_bd() { set_bit(l, 7, 0); }
void CPU::opcode_cb_be() { set_bit_hl(7, 0); }
void CPU::opcode_cb_bf() { set_bit(a, 7, 0); }
void CPU::opcode_cb_c0() { set_bit(b, 0, 1); }
void CPU::opcode_cb_c1() { set_bit(c, 0, 1); }
void CPU::opcode_cb_c2() { set_bit(d, 0, 1); }
void CPU::opcode_cb_c3() { set_bit(e, 0, 1); }
void CPU::opcode_cb_c4() { set_bit(h, 0, 1); }
void CPU::opcode_cb_c5() { set_bit(l, 0, 1); }
void CPU::opcode_cb_c6() { set_bit_hl(0, 1); }
void CPU::opcode_cb_c7() { set_bit(a, 0, 1); }
void CPU::opcode_cb_c8() { set_bit(b, 1, 1); }
void CPU::opcode_cb_c9() { set_bit(c, 1, 1); }
void CPU::opcode_cb_ca() { set_bit(d, 1, 1); }
void CPU::opcode_cb_cb() { set_bit(e, 1, 1); }
void CPU::opcode_cb_cc() { set_bit(h, 1, 1); }
void CPU::opcode_cb_cd() { set_bit(l, 1, 1); }
void CPU::opcode_cb_ce() { set_bit_hl(1, 1); }
void CPU::opcode_cb_cf() { set_bit(a, 1, 1); }
void CPU::opcode_cb_d0() { set_bit(b, 2, 1); }
void CPU::opcode_cb_d1() { set_bit(c, 2, 1); }
void CPU::opcode_cb_d2() { set_bit(d, 2, 1); }
void CPU::opcode_cb_d3() { set_bit(e, 2, 1); }
void CPU::opcode_cb_d4() { set_bit(h, 2, 1); }
void CPU::opcode_cb_d5() { set_bit(l, 2, 1); }
void CPU::opcode_cb_d6() { set_bit_hl(2, 1); }
void CPU::opcode_cb_d7() { set_bit(a, 2, 1); }
void CPU::opcode_cb_d8() { set_bit(b, 3, 1); }
void CPU::opcode_cb_d9() { set_bit(c, 3, 1); }
void CPU::opcode_cb_da() { set_bit(d, 3, 1); }
void CPU::opcode_cb_db() { set_bit(e, 3, 1); }
void CPU::opcode_cb_dc() { set_bit(h, 3, 1); }
void CPU::opcode_cb_dd() { set_bit(l, 3, 1); }
void CPU::opcode_cb_de() { set_bit_hl(3, 1); }
void CPU::opcode_cb_df() { set_bit(a, 3, 1); }
void CPU::opcode_cb_e0() { set_bit(b, 4, 1); }
void CPU::opcode_cb_e1() { set_bit(c, 4, 1); }
void CPU::opcode_cb_e2() { set_bit(d, 4, 1); }
void CPU::opcode_cb_e3() { set_bit(e, 4, 1); }
void CPU::opcode_cb_e4() { set_bit(h, 4, 1); }
void CPU::opcode_cb_e5() { set_bit(l, 4, 1); }
void CPU::opcode_cb_e6() { set_bit_hl(4, 1); }
void CPU::opcode_cb_e7() { set_bit(a, 4, 1); }
void CPU::opcode_cb_e8() { set_bit(b, 5, 1); }
void CPU::opcode_cb_e9() { set_bit(c, 5, 1); }
void CPU::opcode_cb_ea() { set_bit(d, 5, 1); }
void CPU::opcode_cb_eb() { set_bit(e, 5, 1); }
void CPU::opcode_cb_ec() { set_bit(h, 5, 1); }
void CPU::opcode_cb_ed() { set_bit(l, 5, 1); }
void CPU::opcode_cb_ee() { set_bit_hl(5, 1); }
void CPU::opcode_cb_ef() { set_bit(a, 5, 1); }
void CPU::opcode_cb_f0() { set_bit(b, 6, 1); }
void CPU::opcode_cb_f1() { set_bit(c, 6, 1); }
void CPU::opcode_cb_f2() { set_bit(d, 6, 1); }
void CPU::opcode_cb_f3() { set_bit(e, 6, 1); }
void CPU::opcode_cb_f4() { set_bit(h, 6, 1); }
void CPU::opcode_cb_f5() { set_bit(l, 6, 1); }
void CPU::opcode_cb_f6() { set_bit_hl(6, 1); }
void CPU::opcode_cb_f7() { set_bit(a, 6, 1); }
void CPU::opcode_cb_f8() { set_bit(b, 7, 1); }
void CPU::opcode_cb_f9() { set_bit(c, 7, 1); }
void CPU::opcode_cb_fa() { set_bit(d, 7, 1); }
void CPU::opcode_cb_fb() { set_bit(e, 7, 1); }
void CPU::opcode_cb_fc() { set_bit(h, 7, 1); }
void CPU::opcode_cb_fd() { set_bit(l, 7, 1); }
void CPU::opcode_cb_fe() { set_bit_hl(7, 1); }
void CPU::opcode_cb_ff() { set_bit(a, 7, 1); }
}