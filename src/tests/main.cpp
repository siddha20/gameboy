#include <iostream>
#include <stdlib.h>

namespace emulator
{
extern void memory_tests();
extern void memory_structure_tests();
extern void cartridge_tests();
extern void mapper_tests();
extern void cpu_instruction_tests();
extern void ppu_tests();
extern void runner_tests();
}

int main(int argc, char** argv)
{
    emulator::memory_tests();
    emulator::memory_structure_tests();
    emulator::cartridge_tests();
    emulator::mapper_tests();
    emulator::cpu_instruction_tests();
    emulator::ppu_tests();
    emulator::runner_tests();
    return EXIT_SUCCESS;
}