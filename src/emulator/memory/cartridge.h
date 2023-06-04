#pragma once
#include <array>
#include <optional>
#include <vector>
#include "common.h"

namespace emulator
{
/*
 * Currently there is no MBC implemented. Basically only works with ROM only
 * cartridges right now. 
 */
class Cartridge
{
public:
    static constexpr size_t ROM_SIZE  = 16384;
    static constexpr u16 ROM_00_START = 0x0000;
    static constexpr u16 ROM_00_END   = 0x3FFF;
    static constexpr u16 ROM_XX_START = 0x4000;
    static constexpr u16 ROM_XX_END   = 0x7FFF;
    static constexpr u16 ERAM_START   = 0xA000;
    static constexpr u16 ERAM_END     = 0xBFFF;
    Cartridge();

    auto read(u16 address) -> std::optional<u8>;
    bool write(u8 content, u16 address) { /* No op */ return false; }
    void load_rom(const std::vector<char> &rom_data);

private:
    std::array<u8, ROM_SIZE> rom_00;
    std::array<u8, ROM_SIZE> rom_xx;

    auto get_byte(u16 address) -> std::optional<std::reference_wrapper<u8>>;
};
}
