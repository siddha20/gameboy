#pragma once
#include "common.h"

namespace emulator
{
template <typename byte_type=u8>
union Word
{
    struct
    {
        byte_type lo;
        u8 hi;
    };
    u16 word;
};

union LoFlag
{
    struct
    {
        u8 : 4;
        u8 carry_flag : 1; // C
        u8 h_carry_flag : 1; // H
        u8 subtraction_flag : 1; // N
        u8 zero_flag : 1; // Z
    };
    u8 flag_byte;
};

struct Registers
{
    Word<LoFlag> af;
    Word<> bc;
    Word<> de;
    Word<> hl;
};
}