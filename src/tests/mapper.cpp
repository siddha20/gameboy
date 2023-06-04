#include "mapper.h"

namespace emulator
{
void mapper_tests()
{
    emulator::Mapper map{};
    auto &a = map.memory.oam[35];
    assert(a.palette_number == 0);
    assert(a.x_flip == 0);
    assert(a.y_flip == 0);
    assert(a.BGW == 0);
}
}