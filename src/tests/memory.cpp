#include <iostream>
#include "memory.h"
#include "memory_structs.h"

namespace emulator
{
void memory_tests()
{

}

void memory_structure_tests()
{
    emulator::SpriteAttribute a{};
    assert(a.byte[0] == 0);
    assert(a.y_position == 0);
    assert(a.byte[1] == 0);
    assert(a.byte[2] == 0);
    assert(a.byte[3] == 0);
    a.flag_byte = 0b11010000;
    a.y_position = 53;
    a.x_position = 23;
    a.tile_index = 15;
    assert(a.byte[0] == 53);
    assert(a.byte[1] == 23);
    assert(a.byte[2] == 15);
    assert(a.byte[3] == a.flag_byte);
    assert(a.palette_number == 1);
    assert(a.x_flip == 0);
    assert(a.y_flip == 1);
    assert(a.BGW == 1);
    a.y_flip = 0;
    assert(a.y_flip == 0);

    emulator::Palettes p{};
    p.BGP.byte = 0b01101110;
    assert(p.BGP.color_0 == 2);
    assert(p.BGP.color_1 == 3);
    assert(p.BGP.color_2 == 2);
    assert(p.BGP.color_3 == 1);

    std::cout << "Memory structure tests passed." << std::endl;
}
}