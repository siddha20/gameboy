#pragma once
#include <array>
#include <assert.h>
#include <optional>
#include <iostream>
#include "common.h"
#include "memory_structs.h"

namespace emulator
{
class Memory
{
public:
    static constexpr size_t WRAM_SIZE = 8192;
    static constexpr size_t VRAM_SIZE = 8192;
    static constexpr size_t HRAM_SIZE = 127;
    static constexpr size_t OAM_SIZE  = 40;
    static constexpr u16 VRAM_START   = 0x8000;
    static constexpr u16 VRAM_END     = 0x9FFF;
    static constexpr u16 WRAM_START   = 0xC000;
    static constexpr u16 WRAM_END     = 0xDFFF;
    static constexpr u16 MIRROR_START = 0xE000;
    static constexpr u16 MIRROR_END   = 0xFDFF;
    static constexpr u16 SPRITE_START = 0xFE00;
    static constexpr u16 SPRITE_END   = 0xFE9F;
    static constexpr u16 IO_REG_START = 0xFF00;
    static constexpr u16 IO_REG_END   = 0xFF7F;
    static constexpr u16 HRAM_START   = 0xFF80;
    static constexpr u16 HRAM_END     = 0xFFFE;
    static constexpr u16 IE_START     = 0xFFFF;
    static constexpr u16 IE_END       = 0xFFFF;
    std::array<SpriteAttribute, OAM_SIZE> oam;
    JoypadStatus joypad;
    JoypadState joypad_state;
    u8 joypad_out;
    Timer timer;
    LCDControl lcd_control;
    LCDStatus lcd_status;
    LCDPosition lcd_position;
    Palettes palettes;
    Interrupts interrupts;
    u8 SB;
    u8 SC;
    u8 dma_location;

    Memory();

    auto read(u16 address) -> std::optional<u8>;
    bool write(u8 content, u16 address);

private:
    std::array<u8, WRAM_SIZE> wram;
    std::array<u8, VRAM_SIZE> vram;
    std::array<u8, HRAM_SIZE> hram;

    auto get_byte(u16 address) -> std::optional<std::reference_wrapper<u8>>;
};
}