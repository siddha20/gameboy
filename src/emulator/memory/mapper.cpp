#include "mapper.h"
#include "joypad.h"

namespace emulator
{
Mapper::Mapper() 
    : cartridge{}
    , memory{}
    , dma_transfer{0}
{
    // Start up values according to Pan Docs.
    write(0x00, 0xFF05);
    write(0x00, 0xFF06);
    write(0x00, 0xFF07);
    write(0x80, 0xFF10);
    write(0xBF, 0xFF11);
    write(0xF3, 0xFF12);
    write(0xBF, 0xFF14);
    write(0x3F, 0xFF16);
    write(0x00, 0xFF17);
    write(0xBF, 0xFF19);
    write(0x7F, 0xFF1A);
    write(0xFF, 0xFF1B);
    write(0x9F, 0xFF1C);
    write(0xBF, 0xFF1E);
    write(0xFF, 0xFF20);
    write(0x00, 0xFF21);
    write(0x00, 0xFF22);
    write(0xBF, 0xFF23);
    write(0x77, 0xFF24);
    write(0xF3, 0xFF25);
    write(0xF1, 0xFF26);
    write(0x91, 0xFF40);
    write(0x00, 0xFF42);
    write(0x00, 0xFF43);
    write(0x00, 0xFF45);
    write(0xFC, 0xFF47);
    write(0xFF, 0xFF48);
    write(0xFF, 0xFF49);
    write(0x00, 0xFF4A);
    write(0x00, 0xFF4B);
    write(0x00, 0xFFFF);
}

/* Returns 0xFF on bad reads. */
u8 Mapper::read(u16 address)
{
    auto memory_byte = memory.read(address);
    auto cartridge_byte = cartridge.read(address);
    
    // Only one or none should return a byte.
    bool memory_read = static_cast<bool>(memory_byte);
    bool cartridge_read = static_cast<bool>(cartridge_byte);

    assert((memory_read ^ cartridge_read) || !(memory_read || cartridge_read));

    if (address == 0xFF00) return Joypad::get_joypad_state(memory.joypad, memory.joypad_state);

    if (memory_byte) return *memory_byte;
    else if (cartridge_byte) return *cartridge_byte;
    else return 0xFF;
}

/* Returns true if written to a single address. */
bool Mapper::write(u8 content, u16 address)
{
    bool memory_write = memory.write(content, address);
    bool cartridge_write = cartridge.write(content, address);

    // Only one or none should do a write.
    assert((memory_write ^ cartridge_write) || !(memory_write || cartridge_write));

    if (address == 0xFF46) dma_transfer = true;

    return memory_write ^ cartridge_write;
}

bool Mapper::start_dma()
{
    if (dma_transfer)
    {
        dma_transfer = false;
        return true;
    }
    return false;
}
}