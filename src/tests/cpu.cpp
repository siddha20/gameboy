#include <iostream>
#include <cassert>
#include <bitset>
#include "cpu.h"
#include "common.h"

namespace emulator
{
void cpu_instruction_tests()
{
    Mapper mapper{};
    CPU cpu{mapper};
    cpu.program_counter.word = 0xC000;
    cpu.mapper.write(5, cpu.program_counter.word);
    cpu.mapper.write(2, cpu.program_counter.word + 1);
    cpu.ld_16_imd16(cpu.registers.bc);
    assert(cpu.registers.bc.word == 517);

    cpu.program_counter.word = 0xC250;
    cpu.mapper.write(0x55, cpu.program_counter.word);
    cpu.mapper.write(0xC2, cpu.program_counter.word + 1);
    cpu.ld_16_addr16_from(cpu.registers.bc);
    assert(cpu.mapper.read(0xC255) == 5);
    assert(cpu.mapper.read(0xC255 + 1) == 2);

    u8 a = 0;
    cpu.add(a, 255);
    assert(a == 255);
    assert(cpu.registers.af.lo.carry_flag == 0);

    a = 2;
    cpu.add(a, 255);
    assert(a == 1);
    assert(cpu.registers.af.lo.carry_flag == 1);

    cpu.program_counter.word = 0xFF81;
    cpu.mapper.write(254, cpu.program_counter.word);
    a = 0;
    cpu.add_imd8(a);
    assert(a == 254);
    assert(cpu.registers.af.lo.carry_flag == 0);

    cpu.stack_pointer.word = 10;
    cpu.program_counter.word = 0xFF81;
    cpu.mapper.write(-9, cpu.program_counter.word);
    cpu.add_16_imds8(cpu.stack_pointer);
    assert(cpu.stack_pointer.word == 1);

    a = 0x85;
    cpu.registers.af.lo.carry_flag = 0;
    cpu.rot<0, 0, -1>(a);
    assert(a == 0x0A + 1) ;
    assert(cpu.registers.af.lo.carry_flag == 1);

    a = 0x95;
    cpu.registers.af.lo.carry_flag = 1;
    cpu.rot<0, 1, -1>(a);
    assert(a == 0x2B);
    assert(cpu.registers.af.lo.carry_flag == 1);

    a = 0x3B;
    cpu.registers.af.lo.carry_flag = 0;
    cpu.rot<0, 0, 1>(a);
    assert(a == 0x9D);
    assert(cpu.registers.af.lo.carry_flag == 1);

    a = 0x81;
    cpu.registers.af.lo.carry_flag = 0;
    cpu.rot<0, 1, 1>(a);
    assert(a == 0x40);
    assert(cpu.registers.af.lo.carry_flag == 1);

    a = 0x80;
    cpu.registers.af.lo.carry_flag = 0;
    cpu.sla(a);
    assert(a == 0);
    assert(cpu.registers.af.lo.carry_flag == 1);
    assert(cpu.registers.af.lo.zero_flag == 1);

    a = 0x8A;
    cpu.registers.af.lo.carry_flag = 0;
    cpu.sr<0>(a);
    assert(a == 0xC5);
    assert(cpu.registers.af.lo.carry_flag == 0);
    assert(cpu.registers.af.lo.zero_flag == 0);

    a = 0x01;
    cpu.registers.af.lo.carry_flag = 0;
    cpu.sr<1>(a);
    assert(a == 0x00);
    assert(cpu.registers.af.lo.carry_flag == 1);
    assert(cpu.registers.af.lo.zero_flag == 1);

    a = 0xA9;
    cpu.registers.af.lo.carry_flag = 1;
    cpu.swap(a);
    assert(a == 0x9A);
    assert(cpu.registers.af.lo.zero_flag == 0);

    cpu.a = 0x0F;
    cpu.registers.af.lo.h_carry_flag = 0;
    cpu.inc_8(cpu.a);
    assert(cpu.registers.af.lo.h_carry_flag == 1);

    cpu.registers.af.lo.h_carry_flag = 0;
    cpu.h = 0x4C;
    cpu.l = 0x00;
    cpu.opcode_29();
    assert(cpu.registers.af.lo.h_carry_flag == 1);

    cpu.registers.af.lo.h_carry_flag = 0;
    cpu.registers.af.lo.carry_flag = 1;
    a = 0x00;
    cpu.adc(a, 0x0F);
    assert(cpu.registers.af.lo.h_carry_flag == 1);

    cpu.registers.af.lo.flag_byte = 0;
    a = 0x00;
    cpu.sbc(a, 0x00);
    assert(cpu.registers.af.lo.h_carry_flag == 0);

    std::cout << "CPU tests passed.\n"; 
}
}