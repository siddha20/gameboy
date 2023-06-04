#include "cpu.h"

namespace emulator
{
CPU::CPU(Mapper &mapper) 
    : stack_pointer{}
    , program_counter{}
    , mapper{mapper}
    , opcode_table{}
    , registers{}
    , branch_taken{0}
    , jump{0}
    , cb_instruction{0}
    , halt_state{0}
    , interrupt{0}
    , last_instruction_byte{0}
    , cycle_count{0}
    , total_cycles{0}
{
    create_opcode_table();
    create_cb_opcode_table(); 
    create_cycle_tables();

    // Start up values
    program_counter.word = 0x0100;
    stack_pointer.word = 0xFFFE;
    registers.af.word = 0x01B0;
    registers.bc.word = 0x0013;
    registers.de.word = 0x00D8;
    registers.hl.word = 0x014D;
}

void CPU::step()
{
    ++total_cycles;
    update_timers();

    // Currently executing an instruction.
    if (cycle_count > 0)
    {
        --cycle_count;
        return;
    }

    branch_taken = false;
    jump = false;
    cb_instruction = false;
    interrupt = false;

    handle_interrupts();

    if (halt_state) return;

    last_instruction_byte = mapper.read(program_counter.word++);
    last_instruction = opcode_table[last_instruction_byte];
    (this->*last_instruction)();

    if (cb_instruction) cycle_count += cycle_cb_table[last_instruction_byte];
    else if (branch_taken) cycle_count += cycle_branch_table[last_instruction_byte];
    else cycle_count += cycle_table[last_instruction_byte];
    if (interrupt) cycle_count += 20;
}

void CPU::check_interrupt(u8 shift, u16 address)
{
    u8 ie_byte = mapper.memory.interrupts.IE.byte;
    u8 &if_byte = mapper.memory.interrupts.IF.byte;
    if ((ie_byte & (1 << shift)) && (if_byte & (1 << shift)))
    {
        if (halt_state) halt_state = false;
        if (mapper.memory.interrupts.IME)
        {
            set_bit(if_byte, shift, 0);
            interrupt = true;
            mapper.memory.interrupts.IME = 0;
            call(address);
        }
    }
}

void CPU::handle_interrupts()
{
    check_interrupt(0, VBLANK_INTERRUPT);
    check_interrupt(1, LCD_STAT_INTERRUPT);
    check_interrupt(2, TIMER_INTERRUPT);
    check_interrupt(3, SERIAL_INTERRUPT);
    check_interrupt(4, JOYPAD_INTERRUPT);
}

void CPU::incr_timer(u64 cycles)
{
    if ((total_cycles % cycles == 0) && mapper.memory.timer.TAC.enable)
    {
        if (mapper.memory.timer.TIMA == 0xFF)
        {
            mapper.memory.timer.TIMA = mapper.memory.timer.TMA;
            mapper.memory.interrupts.IF.timer = 1;
        }
        else ++mapper.memory.timer.TIMA;
    }
}

void CPU::update_timers()
{
    if (total_cycles % 64 == 0) ++mapper.memory.timer.DIV;
    switch (mapper.memory.timer.TAC.mode)
    {
        case 0b00: incr_timer(256); break;
        case 0b01: incr_timer(4); break;
        case 0b10: incr_timer(16); break;
        case 0b11: incr_timer(64); break;
    }
}

void CPU::set_zero_carry_flags(u32 result, u32 a, u32 b)
{
    set_zero_flag(result);
    set_carry_flag(result);
    set_half_carry_flag_add(a, b);
}

void CPU::set_zero_carry_flags_sub(u32 result, u32 a, u32 b)
{
    set_zero_flag(result);
    set_carry_flag(result);
    set_half_carry_flag_sub(a, b);
}

void CPU::print_debug_info()
{
    // This is for Blargg's tests.
    if(mapper.read(0xFF02) == 0x81)
    {
        char c = static_cast<char>(mapper.read(0xFF01));
        std::cerr << c; 
        mapper.write(0, 0xFF02);
    }

    printf("A: %02X F: %02X B: %02X C: %02X D: %02X E: %02X H: %02X L: %02X SP: %04X PC: 00:%04X (%02X %02X %02X %02X) %u %02X %02X\n",
        a, f, b, c, d, e, h, l, get_sp(), get_pc(), 
        mapper.read(get_pc()),
        mapper.read(get_pc() + 1),
        mapper.read(get_pc() + 2),
        mapper.read(get_pc() + 3),
        mapper.memory.interrupts.IME,
        mapper.memory.interrupts.IE.byte,
        mapper.memory.interrupts.IF.byte);
}
}