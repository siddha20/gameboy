#include "emulator.h"

int main(int argc, char** argv)
{
    std::string rom_path;
    if (argc != 2)
    {
        std::cerr << "Usage: gameboy <path to ROM>" << std::endl;
        return EXIT_FAILURE;
    }
    else rom_path = std::string(argv[1]);

    emulator::Runner r{rom_path};
    r.start();
    return EXIT_SUCCESS;
}