#pragma once
#include <array>
#include <queue>
#include "mapper.h"
#include "common.h"

namespace emulator
{
class PPU
{
public:
    static constexpr size_t TILE_BLOCK_0_START = 0x8000;
    static constexpr size_t TILE_BLOCK_0_END   = 0x87FF;
    static constexpr size_t TILE_BLOCK_1_START = 0x8800;
    static constexpr size_t TILE_BLOCK_1_END   = 0x8FFF;
    static constexpr size_t TILE_BLOCK_2_START = 0x9000;
    static constexpr size_t TILE_BLOCK_2_END   = 0x97FF;
    static constexpr size_t TILE_MAP_0_START = 0x9800;
    static constexpr size_t TILE_MAP_0_END   = 0x9BFF;
    static constexpr size_t TILE_MAP_1_START = 0x9C00;
    static constexpr size_t TILE_MAP_1_END   = 0x9FFF;
    static constexpr size_t TILE_MAP_WIDTH  = 32;
    static constexpr size_t TILE_MAP_HEIGHT = 32;
    static constexpr size_t TILE_SIZE = 16;
    static constexpr size_t TILE_WIDTH = 8;
    static constexpr size_t TILE_HEIGHT = 8;
    static constexpr size_t DISPLAY_WIDTH  = 160;
    static constexpr size_t DISPLAY_HEIGHT = 144;
    static constexpr u64 DMA_TRANSFER_CYCLES = 160;
    static constexpr u64 HBLANK_CYCLES = 204;
    static constexpr u64 VBLANK_CYCLES = 456;
    static constexpr u64 OAM_SEARCH_CYCLES = 80;
    static constexpr u64 DRAW_LINE_CYCLES = 172;

    enum StatMode
    {
        _0_HBlank,
        _1_VBlank,
        _2_OAMSearch,
        _3_DrawLine
    };

    enum LineType
    {
        BACKGROUND,
        WINDOW,
        SPRITE
    };

    struct Color
    {
        u8 id;
        u8 color;
    };

    struct RenderItem
    {
        u8 line;
        std::array<Color, DISPLAY_WIDTH> data;
        LineType line_type;
        RenderItem(u8 line, auto data, LineType line_type)
            : line{line}
            , data{data}
            , line_type{line_type}
        {}
        RenderItem(const RenderItem &item) = default;
    };

    std::queue<RenderItem> render_queue;

    PPU(Mapper &mapper);

    void step();
    auto const &get_line() const { return line; }
    StatMode get_stat_mode() const { return stat_mode; }
    u64 get_mode_cycles() const { return cycle_count; }
    u64 get_total_cycles() const { return total_cycles; }
    u8 get_internal_ly() const { return internal_ly; }
    std::string get_mode_string() const;

private:
    Mapper &mapper;
    u8 &ly = mapper.memory.lcd_status.LY;
    u8 &lyc = mapper.memory.lcd_status.LYC;
    u8 &scy = mapper.memory.lcd_position.SCY;
    u8 &scx = mapper.memory.lcd_position.SCX;
    u8 &wy = mapper.memory.lcd_position.WY;
    u8 &wx = mapper.memory.lcd_position.WX;
    u8 internal_ly;
    std::array<Color, DISPLAY_WIDTH> line;
    StatMode stat_mode;
    u64 cycle_count;
    u64 total_cycles;

    void dma_transfer();
    void set_interrupts();
    void draw_background_line();
    void draw_window_line();
    void draw_sprite_line();
    u8 get_color_byte(ColorByte color, u8 index);

    friend void ppu_tests();
};
}