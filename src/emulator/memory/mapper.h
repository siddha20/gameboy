#pragma once
#include "cartridge.h"
#include "memory.h"

namespace emulator
{
class Mapper
{
public:
    Cartridge cartridge;
    Memory memory;

    Mapper();

    u8 read(u16 address);
    bool write(u8 content, u16 address);
    bool start_dma();

private:
    bool dma_transfer;
};
}