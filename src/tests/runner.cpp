#include "runner.h"

namespace emulator
{
void runner_tests()
{
    // Runner runner{"dmg-acid2.gb"};
    // Runner runner{"tetris.gb"};
    // Runner runner{"drmario.gb"};
    // runner.start();

    Runner run{""};
    run.mapper.write(0x3C, 0x8000);
    run.mapper.write(0x7E, 0x8001);
    run.mapper.write(0x42, 0x8002);
    run.mapper.write(0x42, 0x8003);
    run.mapper.write(0x42, 0x8004);
    run.mapper.write(0x42, 0x8005);
    run.mapper.write(0x42, 0x8006);
    run.mapper.write(0x42, 0x8007);
    run.mapper.write(0x7E, 0x8008);
    run.mapper.write(0x5E, 0x8009);
    run.mapper.write(0x7E, 0x800A);
    run.mapper.write(0x0A, 0x800B);
    run.mapper.write(0x7C, 0x800C);
    run.mapper.write(0x56, 0x800D);
    run.mapper.write(0x38, 0x800E);
    run.mapper.write(0x7C, 0x800F);
    assert(run.mapper.read(0x8000) == 0x3C);
    assert(run.mapper.read(0x8001) == 0x7E);
    assert(run.mapper.read(0x8002) == 0x42);
    assert(run.mapper.read(0x8003) == 0x42);
    assert(run.mapper.read(0x8004) == 0x42);
    assert(run.mapper.read(0x8005) == 0x42);
    assert(run.mapper.read(0x8006) == 0x42);
    assert(run.mapper.read(0x8007) == 0x42);
    assert(run.mapper.read(0x8008) == 0x7E);
    assert(run.mapper.read(0x8009) == 0x5E);
    assert(run.mapper.read(0x800A) == 0x7E);
    assert(run.mapper.read(0x800B) == 0x0A);
    assert(run.mapper.read(0x800C) == 0x7C);
    assert(run.mapper.read(0x800D) == 0x56);
    assert(run.mapper.read(0x800E) == 0x38);
    assert(run.mapper.read(0x800F) == 0x7C);
    run.mapper.write(1, 0x9800);
    run.mapper.write(1, 0x9801);
    run.mapper.write(1, 0x9802);
    run.mapper.write(1, 0x9803);
    run.mapper.write(1, 0x9804);
    run.mapper.write(1, 0x9805);
    run.mapper.write(1, 0x9806);
    run.mapper.write(1, 0x9807);
    run.mapper.write(1, 0x9810);
    run.mapper.write(1, 0x9811);
    run.mapper.write(1, 0x9812);
    run.mapper.write(1, 0x9813);
    run.mapper.write(1, 0x9814);
    run.mapper.write(1, 0x9815);
    run.mapper.write(1, 0x9816);
    run.mapper.write(1, 0x9817);
    run.mapper.write(1, 0x9820);
    run.mapper.write(1, 0x9821);
    run.mapper.write(1, 0x9822);
    run.mapper.write(1, 0x9823);
    run.mapper.write(1, 0x9824);
    run.mapper.write(1, 0x9825);
    run.mapper.write(1, 0x9826);
    run.mapper.write(1, 0x9827);
    run.mapper.write(1, 0x9830);
    run.mapper.write(1, 0x9831);
    run.mapper.write(1, 0x9832);
    run.mapper.write(1, 0x9833);
    run.mapper.write(1, 0x9834);
    run.mapper.write(1, 0x9835);
    run.mapper.write(1, 0x9836);
    run.mapper.write(1, 0x9837);
    run.mapper.write(16, 0xFE00);
    run.mapper.write(8, 0xFE01);
    run.mapper.write(0, 0xFE02);
    run.mapper.write(0b01110000, 0xFE03);

    run.mapper.memory.oam[3].x_position = 32;
    run.mapper.memory.oam[3].y_position = 16;
    run.mapper.memory.oam[3].BGW = 1;

    run.mapper.memory.oam[5].x_position = 52;
    run.mapper.memory.oam[5].y_position = 16;
    run.mapper.memory.oam[5].BGW = 1;

    run.mapper.memory.oam[7].x_position = 44;
    run.mapper.memory.oam[7].y_position = 20;
    run.mapper.memory.oam[7].BGW = 1;

    assert(run.mapper.memory.oam[0].BGW == 0);
    assert(run.mapper.memory.oam[0].y_flip == 1);
    assert(run.mapper.memory.oam[0].x_flip == 1);
    assert(run.mapper.memory.oam[0].palette_number == 1);
    assert(run.mapper.memory.oam[0].x_position == 8);
    assert(run.mapper.memory.oam[0].y_position == 16);
    assert(run.mapper.memory.oam[0].tile_index == 0);

    run.mapper.memory.lcd_control.bg_tile_map = 0;
    run.mapper.memory.lcd_control.bg_enable = 0;
    run.mapper.memory.lcd_control.window_enable = 1;
    run.mapper.memory.lcd_control.obj_enable = 0;
    run.mapper.memory.lcd_control.address_mode = 1;
    run.mapper.memory.lcd_position.WX = 95;
    run.mapper.memory.lcd_position.WY = 40;
    run.mapper.memory.palettes.BGP.byte = 0b11100100;
    run.mapper.memory.palettes.OBP0.byte = 0b11100100;
    run.mapper.memory.palettes.OBP1.byte = 0b11100100;
    run.start();
}
}