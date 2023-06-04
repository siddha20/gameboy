#pragma once
#include <array>
#include "common.h"

namespace emulator
{
union SpriteAttribute
{
    struct
    {
        u8 y_position;
        u8 x_position;
        u8 tile_index;
        union
        {
            struct
            {
                u8 : 4;
                u8 palette_number : 1;
                u8 x_flip : 1;
                u8 y_flip : 1;
                u8 BGW : 1;
            };
            u8 flag_byte;
        };
    };
    u8 byte[4];
};

union JoypadStatus
{
    struct
    {
        u8 right_or_A : 1;
        u8 left_or_B : 1;
        u8 up_or_select : 1;
        u8 down_or_start : 1;
        u8 direction_keys : 1;
        u8 button_keys : 1;
        u8 : 2;
    };
    u8 flag_byte;
};

struct JoypadState
{
    u8 direction_keys_state;
    u8 action_keys_state;
};

// TODO: Implement serial transfer.
struct SerialTransfer { };

struct Timer
{
    u8 DIV; // Divider register
    u8 TIMA; // Timer counter
    u8 TMA; // Timer modulo
    // u8 TAC; // Timer control
    union // Timer control
    {
        struct
        {
            u8 mode : 2;
            u8 enable : 1;
            u8 : 5;
        };
        u8 flag_byte;
    } TAC; 
};

// TODO: Implement audio. 
struct Audio { };

// TODO: Implement wave pattern. 
struct WavePattern { };

union LCDControl
{
    struct
    {
        u8 bg_enable : 1;
        u8 obj_enable : 1;
        u8 obj_size : 1;
        u8 bg_tile_map : 1;
        u8 address_mode : 1;
        u8 window_enable : 1;
        u8 window_tile_map : 1;
        u8 lcd_enable : 1;
    };
    u8 flag_byte;
};

struct LCDStatus
{
    u8 LY; // LCD Y coordinate [read only]
    u8 LYC; // LY compare
    union // LCD status
    {
        struct
        {
            u8 mode : 2;
            u8 lyc_ly : 1;
            u8 hblank_stat_interrupt : 1;
            u8 vblank_stat_interrupt : 1;
            u8 oam_stat_interrupt : 1;
            u8 lyc_ly_stat_interrupt : 1;
            u8 : 1;
        };
        u8 flag_byte;
    } STAT; 
};

struct LCDPosition
{
    u8 SCY; // Viewport Y position
    u8 SCX; // Viewport X position
    u8 WY; // Window Y position
    u8 WX; // Window X position
};

union ColorByte
{
    struct 
    {
        u8 color_0 : 2;
        u8 color_1 : 2;
        u8 color_2 : 2;
        u8 color_3 : 2;
    };
    u8 byte;
};

struct Palettes
{
    ColorByte BGP; // Background palette data
    ColorByte OBP0; // Object palette 0
    ColorByte OBP1; // Object palette 1
};

union InterruptByte
{
    struct 
    {
        u8 vblank : 1;
        u8 lcd_stat : 1;
        u8 timer : 1;
        u8 serial : 1;
        u8 joypad : 1;
        u8 : 3;
    };
    u8 byte;
};

struct Interrupts
{
    u8 IME; // Interrupt master enable flag [write only]
    InterruptByte IE; // Interrupt enable
    InterruptByte IF; // Interrupt flag
};
}