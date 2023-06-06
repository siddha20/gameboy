#include <optional>
#include "memory.h"
#include "common.h"

namespace emulator
{
Memory::Memory() 
    : wram{}
    , vram{}
    , hram{}
    , oam{}
    , joypad{}
    , joypad_out{}
    , timer{}
    , lcd_control{}
    , lcd_status{}
    , lcd_position{}
    , palettes{}
    , interrupts{}
    , SB{}
    , SC{}
{}

auto Memory::read(u16 address) -> std::optional<u8>
{
    auto byte = get_byte(address);
    if (byte)
    {
        if (address == 0xFF00) return joypad_out; 
        else return byte->get();
    }
    else return {};
}

bool Memory::write(u8 content, u16 address)
{
    // Add potential no write allows here. if (address = xxxx) return false;
    auto byte = get_byte(address);
    if (byte) 
    {
        switch (address)
        {
            case 0xFF04: byte->get() = 0x00; break; // Reset DIV
            case 0xFF41: byte->get() += (content & 0xF8); break; // The last 3 bits of 0xFF41 are read only
            default: byte->get() = content;
        }
        // if (address == 0xFF04) byte->get() = 0x00; // Reset DIV
        // else if (address == 0xFF41) byte->get() +=  (content & 0xF8); // The last 3 bits of 0xFF41 are read only
        // else byte->get() = content;
        return true;
    }
    else return false; 
}

auto Memory::get_byte(u16 address) -> std::optional<std::reference_wrapper<u8>>
{
    auto addr_between = [address](u16 a, u16 b) { return is_between(a, b, address); };
    if (addr_between(VRAM_START, VRAM_END)) return vram[address - VRAM_START];
    else if (addr_between(WRAM_START, WRAM_END)) return wram[address - WRAM_START];
    else if (addr_between(MIRROR_START, MIRROR_END)) return wram[address - MIRROR_START];
    else if (addr_between(SPRITE_START, SPRITE_END)) 
    {
        switch ((address - SPRITE_START) % 4)
        {
            case 0: return oam[(address - SPRITE_START)/4].y_position;
            case 1: return oam[(address - SPRITE_START)/4].x_position;
            case 2: return oam[(address - SPRITE_START)/4].tile_index;
            case 3: return oam[(address - SPRITE_START)/4].flag_byte;
        }
    }
    else if (addr_between(HRAM_START, HRAM_END)) return hram[address - HRAM_START];
    // Begin I/O Ranges
    switch (address)
    {
        case 0xFF00: return joypad.flag_byte;
        case 0xFF01: return SB;
        case 0xFF02: return SC;
        case 0xFF04: return timer.DIV;
        case 0xFF05: return timer.TIMA;
        case 0xFF06: return timer.TMA;
        case 0xFF07: return timer.TAC.flag_byte;
        case 0xFF0F: return interrupts.IF.byte;
        case 0xFF40: return lcd_control.flag_byte;
        case 0xFF41: return lcd_status.STAT.flag_byte;
        case 0xFF42: return lcd_position.SCY;
        case 0xFF43: return lcd_position.SCX;
        case 0xFF44: return lcd_status.LY;
        case 0xFF45: return lcd_status.LYC;
        case 0xFF46: return dma_location;
        case 0xFF47: return palettes.BGP.byte;
        case 0xFF48: return palettes.OBP0.byte;
        case 0xFF49: return palettes.OBP1.byte;
        case 0xFF4A: return lcd_position.WY;
        case 0xFF4B: return lcd_position.WX;
        case 0xFFFF: return interrupts.IE.byte;
    }
    // End I/O Ranges 
    return {};
}
}