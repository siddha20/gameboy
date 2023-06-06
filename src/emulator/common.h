#pragma once
#include <iostream>
#include <stdlib.h>

namespace emulator
{
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8  = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

template<typename T>
inline bool is_between(T lower, T upper, T x)
{
    return static_cast<bool>((lower <= x) && (x <= upper));
}

inline u16 join(u8 lsb, u8 msb)
{
    return (static_cast<u16>(lsb)) + (static_cast<u16>(msb) << 8);
}

inline void set_bit(u8 &byte, u8 index, u8 state)
{
    if (state) byte |= (1 << index);
    else byte &= ~(1 << index);
}
}