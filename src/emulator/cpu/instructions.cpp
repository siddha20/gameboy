#include <bit>
#include <iostream>
#include <bitset>
#include "cpu.h"

namespace emulator
{
void CPU::ld_8_imd8_ind(Word<u8> reg)
{
    u8 byte = mapper.read(program_counter.word++);
    mapper.write(byte, reg.word);
}

void CPU::ld_8_imd8(u8 &byte)
{
    byte = mapper.read(program_counter.word++);
}

void CPU::ld_8_addr16(u8 &byte)
{
    Word<> address{};
    address.lo = mapper.read(program_counter.word++);
    address.hi = mapper.read(program_counter.word++);
    byte = mapper.read(address.word);
}

void CPU::ld_8_addr16_from(u8 byte)
{
    Word<> address{};
    address.lo = mapper.read(program_counter.word++);
    address.hi = mapper.read(program_counter.word++);
    mapper.write(byte, address.word);
}

void CPU::ldh_8_addr16(u8 &byte)
{
    Word<> address{};
    address.lo = mapper.read(program_counter.word++);
    address.hi = 0xFF;
    byte = mapper.read(address.word);
}

void CPU::ldh_8_addr16_from(u8 byte)
{
    Word<> address{};
    address.lo = mapper.read(program_counter.word++);
    address.hi = 0xFF;
    mapper.write(byte, address.word);
}

void CPU::ld_16_imd16(Word<u8> &reg)
{
    reg.lo = mapper.read(program_counter.word++);
    reg.hi = mapper.read(program_counter.word++);
}

void CPU::ld_16_addr16_from(Word<u8> reg)
{
    Word<> address{};
    address.lo = mapper.read(program_counter.word++);
    address.hi = mapper.read(program_counter.word++);
    mapper.write(reg.lo, address.word);
    mapper.write(reg.hi, address.word + 1);
}

void CPU::push(Word<u8> reg)
{
    mapper.write(reg.hi, --stack_pointer.word);
    mapper.write(reg.lo, --stack_pointer.word);
}

void CPU::pop(Word<u8> &reg)
{
    reg.lo = mapper.read(stack_pointer.word++);
    reg.hi = mapper.read(stack_pointer.word++);
}

void CPU::push(Word<LoFlag> reg)
{
    mapper.write(reg.hi, --stack_pointer.word);
    mapper.write(reg.lo.flag_byte, --stack_pointer.word);
}

void CPU::pop(Word<LoFlag> &reg)
{
    reg.lo.flag_byte = mapper.read(stack_pointer.word++) & 0xF0;
    reg.hi = mapper.read(stack_pointer.word++);
}


void CPU::add(u8 &byte_x, u8 byte_y)
{
    u32 result = byte_x + byte_y;
    registers.af.lo.subtraction_flag = 0;
    set_zero_carry_flags(result, byte_x, byte_y);
    byte_x = result;
}

void CPU::add_imd8(u8 &byte)
{
    add(byte, mapper.read(program_counter.word++));
}

void CPU::add_16(Word<u8> &reg_x, Word<u8> reg_y)
{
    u32 result = reg_x.word + reg_y.word;
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = (((reg_x.word & 0x0FFF) + (reg_y.word & 0x0FFF)) > 0x0FFF);
    registers.af.lo.carry_flag = (result > 0xFFFF);
    reg_x.word = result;
}

void CPU::add_16_imds8(Word<u8> &reg)
{
    s8 data = static_cast<s8>(mapper.read(program_counter.word++));
    u32 result = reg.word + data;
    registers.af.lo.zero_flag = 0;
    registers.af.lo.subtraction_flag = 0;
    if (data > 0)
    {
        registers.af.lo.h_carry_flag = (((reg.lo & 0x000F) + (data & 0x000F)) > 0x000F);
        registers.af.lo.carry_flag = ((reg.lo + data) > 0x00FF);
    }
    else
    {
        registers.af.lo.h_carry_flag = (result & 0x000F) <= (reg.lo & 0x000F);
        registers.af.lo.carry_flag =  (result & 0x00FF) <= (reg.lo & 0x00FF);
    }
    reg.word = result;
}

void CPU::ldhl()
{
    s8 data = static_cast<s8>(mapper.read(program_counter.word++));
    u32 result = stack_pointer.word + data;
    registers.af.lo.zero_flag = 0;
    registers.af.lo.subtraction_flag = 0;
    if (data > 0)
    {
        registers.af.lo.h_carry_flag = (((stack_pointer.lo & 0x000F) + (data & 0x000F)) > 0x000F);
        registers.af.lo.carry_flag = ((stack_pointer.lo + data) > 0x00FF);
    }
    else
    {
        registers.af.lo.h_carry_flag = (result & 0x000F) <= (stack_pointer.lo & 0x000F);
        registers.af.lo.carry_flag =  (result & 0x00FF) <= (stack_pointer.lo & 0x00FF);
    }
    registers.hl.word = result;
}

void CPU::adc(u8 &byte_x, u8 byte_y)
{
    u8 carry = registers.af.lo.carry_flag;
    u32 result = byte_x + byte_y + carry;
    registers.af.lo.subtraction_flag = 0;
    set_zero_flag(result);
    set_carry_flag(result);
    registers.af.lo.h_carry_flag = (((byte_x & 0x0F) + (byte_y & 0x0F) + carry) > 0x0F);
    byte_x = result;
}

void CPU::adc_imd8(u8 &byte)
{
    adc(byte, mapper.read(program_counter.word++));
}

void CPU::sub(u8 &byte_x, u8 byte_y)
{
    u32 result = byte_x - byte_y;
    registers.af.lo.subtraction_flag = 1;
    set_zero_flag(result);
    registers.af.lo.h_carry_flag = (byte_x & 0x0F) < (byte_y & 0x0F);
    registers.af.lo.carry_flag = (byte_x & 0xFF) < (byte_y & 0xFF);
    byte_x = result;
}

void CPU::sub_imd8(u8 &byte)
{
    sub(byte, mapper.read(program_counter.word++));
}

void CPU::sbc(u8 &byte_x, u8 byte_y)
{
    u8 carry = registers.af.lo.carry_flag;
    u32 result = byte_x - byte_y - carry;
    registers.af.lo.subtraction_flag = 1;
    set_zero_flag(result);
    registers.af.lo.h_carry_flag = (((byte_x & 0x0F) < ((byte_y & 0x0F) + carry)));
    registers.af.lo.carry_flag = (((byte_x & 0xFF) < ((byte_y & 0xFF) + carry)));
    byte_x = result;
}

void CPU::sbc_imd8(u8 &byte)
{
    sbc(byte, mapper.read(program_counter.word++));
}

void CPU::m_and(u8 &byte_x, u8 byte_y)
{
    u32 result = byte_x & byte_y;
    registers.af.lo.zero_flag = (result == 0);
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 1;
    registers.af.lo.carry_flag = 0;
    byte_x = result;
}

void CPU::m_and_imd8(u8 &byte_x)
{
    m_and(byte_x, mapper.read(program_counter.word++));
}

void CPU::m_or(u8 &byte_x, u8 byte_y)
{
    u32 result = byte_x | byte_y;
    set_zero_flag(result);
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 0;
    registers.af.lo.carry_flag = 0;
    byte_x = result;
}

void CPU::m_or_imd8(u8 &byte_x)
{
    m_or(byte_x, mapper.read(program_counter.word++));
}

void CPU::m_xor(u8 &byte_x, u8 byte_y)
{
    u32 result = byte_x ^ byte_y;
    set_zero_flag(result);
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 0;
    registers.af.lo.carry_flag = 0;
    byte_x = result;
}

void CPU::m_xor_imd8(u8 &byte_x)
{
    m_xor(byte_x, mapper.read(program_counter.word++));
}

void CPU::m_cp(u8 &byte_x, u8 byte_y)
{
    u32 result = byte_x - byte_y;
    registers.af.lo.subtraction_flag = 1;
    set_zero_flag(result);
    registers.af.lo.h_carry_flag = (byte_x & 0x0F) < (byte_y & 0x0F);
    registers.af.lo.carry_flag = (byte_x & 0xFF) < (byte_y & 0xFF);
}

void CPU::m_cp_imd8(u8 &byte)
{
    m_cp(byte, mapper.read(program_counter.word++));
}

void CPU::inc_8(u8 &byte)
{
    u32 result = byte + 1;
    set_zero_flag(result);
    registers.af.lo.subtraction_flag = 0;
    set_half_carry_flag_add(byte, 1);
    byte = result;
}

void CPU::inc_8_ind(Word<u8> reg)
{
    u32 data = mapper.read(reg.word);
    ++data;
    set_zero_flag(data);
    registers.af.lo.subtraction_flag = 0;
    set_half_carry_flag_add(data - 1, 1);
    mapper.write(data, reg.word);
}

void CPU::dec_8(u8 &byte)
{
    u32 result = byte - 1;
    set_zero_flag(result);
    registers.af.lo.subtraction_flag = 1;
    set_half_carry_flag_sub(byte, 1);
    byte = result;
}

void CPU::dec_8_ind(Word<u8> reg)
{
    u32 data = mapper.read(reg.word);
    --data;
    set_zero_flag(data);
    registers.af.lo.subtraction_flag = 1;
    set_half_carry_flag_sub(data + 1, 1);
    mapper.write(data, reg.word);
}

void CPU::daa()
{
    if (registers.af.lo.subtraction_flag)
    {
        if (registers.af.lo.carry_flag) a -= 0x60;
        if (registers.af.lo.h_carry_flag) a -= 0x6;
    }
    else
    {
        if (registers.af.lo.carry_flag || a > 0x99)
        {
            a += 0x60;
            registers.af.lo.carry_flag = 1;
        }
        if (registers.af.lo.h_carry_flag || (a & 0xF) > 0x9) a += 0x6;
    }
    set_zero_flag(a);
    registers.af.lo.h_carry_flag = 0;
}

void CPU::cpl()
{
    a = ~a;
    registers.af.lo.subtraction_flag = 1;
    registers.af.lo.h_carry_flag = 1;
}

void CPU::ccf()
{
    registers.af.lo.carry_flag ^= 1;
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 0;
}

void CPU::scf()
{
    registers.af.lo.carry_flag = 1;
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 0;
}

void CPU::halt()
{
    halt_state = true;
}

void CPU::stop()
{
    ++program_counter.word;
}

void CPU::jump_addr16(bool branch)
{
    Word<> address{};
    address.lo = mapper.read(program_counter.word++);
    address.hi = mapper.read(program_counter.word++);
    if (branch)
    {
        jump = true;
        branch_taken = true;
        program_counter.word = address.word;
    }
}

void CPU::jump_imds8(bool branch)
{
    s8 data = static_cast<s8>(mapper.read(program_counter.word++));
    u16 address = program_counter.word + data;
    if (branch)
    {
        jump = true;
        branch_taken = true;
        program_counter.word = address;
    }
}

void CPU::call(u16 address)
{
    jump = true;
    // ++program_counter.word;
    push(program_counter);
    program_counter.word = address; 
}

void CPU::call_addr16(bool branch)
{
    Word<> address{};
    address.lo = mapper.read(program_counter.word++);
    address.hi = mapper.read(program_counter.word++);
    if (branch)
    {
        branch_taken = true;
        call(address.word);
    }
}

template <bool enable_interrupts>
void CPU::ret(bool branch)
{
    if (branch)
    {
        jump = true;
        branch_taken = true;
        pop(program_counter);
        if (enable_interrupts) mapper.memory.interrupts.IME = 1;
    }
}
template void CPU::ret<0>(bool branch);
template void CPU::ret<1>(bool branch);

template<bool set_zero, bool use_carry, int direction>
void CPU::rot(u8 &byte)
{
    u8 result = std::rotr(byte, direction);
    u8 end_bit = direction == 1 ? 0 : 7;
    u8 start_bit = 7 - end_bit;
    if (use_carry) set_bit(result, start_bit, registers.af.lo.carry_flag);
    registers.af.lo.carry_flag = ((byte & (1 << end_bit)) != 0);
    if (set_zero) set_zero_flag(result);
    else registers.af.lo.zero_flag = 0;
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 0;
    byte = result;
}
template void CPU::rot<1, 1, 1>(u8 &byte);
template void CPU::rot<1, 1,-1>(u8 &byte);
template void CPU::rot<1, 0, 1>(u8 &byte);
template void CPU::rot<1, 0,-1>(u8 &byte);
template void CPU::rot<0, 1, 1>(u8 &byte);
template void CPU::rot<0, 1,-1>(u8 &byte);
template void CPU::rot<0, 0, 1>(u8 &byte);
template void CPU::rot<0, 0,-1>(u8 &byte);

template<bool use_carry, int direction>
void CPU::rot_hl()
{
    u8 byte = mapper.read(registers.hl.word);
    rot<1, use_carry, direction>(byte);
    mapper.write(byte, registers.hl.word);
}
template void CPU::rot_hl<1, 1>();
template void CPU::rot_hl<1,-1>();
template void CPU::rot_hl<0, 1>();
template void CPU::rot_hl<0,-1>();

void CPU::sla(u8 &byte)
{
    u8 result = byte << 1;
    registers.af.lo.carry_flag = ((byte & (1 << 7)) != 0);
    set_zero_flag(result);
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 0;
    byte = result;
}

void CPU::sla_hl()
{
    u8 byte = mapper.read(registers.hl.word);
    sla(byte);
    mapper.write(byte, registers.hl.word);
}

template<bool logical>
void CPU::sr(u8 &byte)
{
    u8 result = byte >> 1;
    registers.af.lo.carry_flag = ((byte & (1 << 0)) != 0);
    set_bit(result, 7, !logical && ((byte & (1 << 7)) != 0));
    set_zero_flag(result);
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 0;
    byte = result;
}
template void CPU::sr<0>(u8 &byte);
template void CPU::sr<1>(u8 &byte);

template<bool logical>
void CPU::sr_hl()
{
    u8 byte = mapper.read(registers.hl.word);
    sr<logical>(byte);
    mapper.write(byte, registers.hl.word);
}
template void CPU::sr_hl<0>();
template void CPU::sr_hl<1>();

void CPU::swap(u8 &byte)
{
    u8 result = byte << 4;
    result |= byte >> 4;
    set_zero_flag(result);
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 0;
    registers.af.lo.carry_flag = 0;
    byte = result;
}

void CPU::swap_hl()
{
    u8 byte = mapper.read(registers.hl.word);
    swap(byte);
    mapper.write(byte, registers.hl.word);
}

void CPU::test_bit(u8 byte, u8 index)
{
    registers.af.lo.zero_flag = !((byte & (1 << index)) != 0);
    registers.af.lo.subtraction_flag = 0;
    registers.af.lo.h_carry_flag = 1;
}

void CPU::set_bit_hl(u8 index, u8 state)
{
    u8 byte = mapper.read(registers.hl.word);
    set_bit(byte, index, state);
    mapper.write(byte, registers.hl.word);
}

void CPU::cb()
{
    cb_instruction = true;
    last_instruction_byte = mapper.read(program_counter.word++);
    last_instruction = cb_opcode_table.at(last_instruction_byte);
    (this->*last_instruction)();
}
}