#include <iostream>
#include <cassert>
#include "cartridge.h"

namespace emulator
{
Cartridge::Cartridge() 
    : rom_00{}
    , rom_xx{}
{}

auto Cartridge::read(u16 address) -> std::optional<u8>
{
    auto byte = get_byte(address);
    if (byte) return byte->get();
    else return {};
}

auto Cartridge::get_byte(u16 address) -> std::optional<std::reference_wrapper<u8>>
{
    auto addr_between = [address](u16 a, u16 b) { return is_between(a, b, address); };
    if (addr_between(ROM_00_START, ROM_00_END)) return rom_00[address - ROM_00_START];
    else if (addr_between(ROM_XX_START, ROM_XX_END)) return rom_xx[address - ROM_XX_START];
    else return {};
}

void Cartridge::load_rom(const std::vector<char> &rom_data)
{
    assert(rom_data.size() <= ROM_SIZE * 2);
    if (rom_data.size() > ROM_SIZE)
    {
        std::copy(rom_data.begin(), rom_data.begin() + ROM_SIZE, rom_00.begin());
        std::copy(rom_data.begin() + ROM_SIZE, rom_data.end(), rom_xx.begin());
    }
    else std::copy(rom_data.begin(), rom_data.end(), rom_00.begin());
}
}
