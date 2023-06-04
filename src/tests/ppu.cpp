#include <cassert>
#include <bitset>
#include "ppu.h"
#include "cpu.h"

namespace emulator
{
void ppu_tests()
{
    Mapper mapper{};
    PPU ppu{mapper};
    CPU cpu{mapper};

    cpu.mapper.write(5, 0xFF81);
    assert(ppu.mapper.read(0xFF81) == 5);

    ppu.mapper.write(0x3C, 0x8000);
    ppu.mapper.write(0x7E, 0x8001);
    ppu.mapper.write(0x42, 0x8002);
    ppu.mapper.write(0x42, 0x8003);
    ppu.mapper.write(0x42, 0x8004);
    ppu.mapper.write(0x42, 0x8005);
    ppu.mapper.write(0x42, 0x8006);
    ppu.mapper.write(0x42, 0x8007);
    ppu.mapper.write(0x7E, 0x8008);
    ppu.mapper.write(0x5E, 0x8009);
    ppu.mapper.write(0x7E, 0x800A);
    ppu.mapper.write(0x0A, 0x800B);
    ppu.mapper.write(0x7C, 0x800C);
    ppu.mapper.write(0x56, 0x800D);
    ppu.mapper.write(0x38, 0x800E);
    ppu.mapper.write(0x7C, 0x800F);
    assert(ppu.mapper.read(0x8000) == 0x3C);
    assert(ppu.mapper.read(0x8001) == 0x7E);
    assert(ppu.mapper.read(0x8002) == 0x42);
    assert(ppu.mapper.read(0x8003) == 0x42);
    assert(ppu.mapper.read(0x8004) == 0x42);
    assert(ppu.mapper.read(0x8005) == 0x42);
    assert(ppu.mapper.read(0x8006) == 0x42);
    assert(ppu.mapper.read(0x8007) == 0x42);
    assert(ppu.mapper.read(0x8008) == 0x7E);
    assert(ppu.mapper.read(0x8009) == 0x5E);
    assert(ppu.mapper.read(0x800A) == 0x7E);
    assert(ppu.mapper.read(0x800B) == 0x0A);
    assert(ppu.mapper.read(0x800C) == 0x7C);
    assert(ppu.mapper.read(0x800D) == 0x56);
    assert(ppu.mapper.read(0x800E) == 0x38);
    assert(ppu.mapper.read(0x800F) == 0x7C);

    ppu.mapper.write(1, 0x9800);

    ppu.mapper.memory.lcd_control.bg_tile_map = 1;
    ppu.mapper.memory.lcd_control.bg_enable = 1;
    ppu.mapper.memory.lcd_control.address_mode = 1;
    ppu.mapper.memory.palettes.BGP.byte = 0b11100100;
    assert(ppu.mapper.memory.lcd_control.bg_tile_map == 1);
    assert(ppu.mapper.memory.lcd_control.address_mode == 1);
    assert(ppu.scy == 0);
    ppu.ly = 0;
    ppu.draw_background_line();
    // std::transform(std::begin(ppu.line), std::begin(ppu.line) + 8, std::ostream_iterator<u16>(std::cout, " "),
    //                [](PPU::Color a) { return a.color; });
    std::array<u8, 8> array_a = {0, 2, 3, 3, 3, 3, 2, 0};
    std::array<u8, 8> array_b;
    for (int i = 0; i < 8; i++) array_b[i] = ppu.line[i].color;
    assert(array_a == array_b);

    std::cout << "PPU tests passed.\n";
}
}