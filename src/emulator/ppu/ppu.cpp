#include "ppu.h"
#include "common.h"

namespace emulator
{
PPU::PPU(Mapper &mapper)
    : mapper(mapper)
    , internal_ly{0}
    , line{}
    , stat_mode{_2_OAMSearch}
    , cycle_count{0}
    , total_cycles{0}
{}

void PPU::step()
{
    static u64 dma_cycles{};
    ++total_cycles;

    if (mapper.start_dma()) 
    { 
        dma_cycles = 160;
        dma_transfer(); 
    }
    if (dma_cycles > 0) --dma_cycles;

    // If LCD is disabled, reset and exit.
    if (!mapper.memory.lcd_control.lcd_enable)
    {
        mapper.memory.lcd_status.STAT.mode = 0;
        stat_mode = _2_OAMSearch;
        ly = 0;
        cycle_count = 0;
        return;
    }

    set_interrupts();

    cycle_count++;

    switch (stat_mode)
    {
    case _0_HBlank:
        mapper.memory.lcd_status.STAT.mode = _0_HBlank;
        if (cycle_count == HBLANK_CYCLES)
        {
            cycle_count = 0;
            if (++ly > 143) stat_mode = _1_VBlank;
            else stat_mode = _2_OAMSearch;
        }
        break;

    case _1_VBlank:
        mapper.memory.lcd_status.STAT.mode = _1_VBlank;
        if (cycle_count == VBLANK_CYCLES)
        {
            cycle_count = 0;
            if (++ly > 153)
            {
                ly = 0;
                internal_ly = 0;
                stat_mode = _2_OAMSearch;
            }
        }
        break;

    case _2_OAMSearch:
        mapper.memory.lcd_status.STAT.mode = _2_OAMSearch;
        if (cycle_count == OAM_SEARCH_CYCLES)
        {
            cycle_count = 0;
            stat_mode = _3_DrawLine;
        }
        break;

    case _3_DrawLine:
        // mapper.memory.lcd_status.STAT.mode = _3_DrawLine;
        if (cycle_count == DRAW_LINE_CYCLES)
        {
            cycle_count = 0;
            draw_background_line();
            draw_window_line();
            draw_sprite_line();
            stat_mode = _0_HBlank;
        }
        break;
    }
}

void PPU::dma_transfer()
{
    u16 source = mapper.memory.dma_location << 8;
    for (u8 i = 0; i < 0xA0; i++) mapper.write(mapper.read(source + i), mapper.memory.SPRITE_START + i);
}

void PPU::set_interrupts()
{
    mapper.memory.lcd_status.STAT.lyc_ly = (ly == lyc);
    bool cond_0 = (mapper.memory.lcd_status.STAT.lyc_ly_stat_interrupt && mapper.memory.lcd_status.STAT.lyc_ly);
    bool cond_1 = (mapper.memory.lcd_status.STAT.hblank_stat_interrupt && (stat_mode == _0_HBlank));
    bool cond_2 = (mapper.memory.lcd_status.STAT.vblank_stat_interrupt && (stat_mode == _1_VBlank));
    bool cond_3 = (mapper.memory.lcd_status.STAT.oam_stat_interrupt    && (stat_mode == _2_OAMSearch));
    mapper.memory.interrupts.IF.lcd_stat = cond_0 || cond_1 || cond_2 || cond_3;
    mapper.memory.interrupts.IF.vblank = (stat_mode == _1_VBlank);
}

void PPU::draw_background_line()
{
    if (!mapper.memory.lcd_control.bg_enable) return;

    u16 tilemap_source = !mapper.memory.lcd_control.bg_tile_map ?
        TILE_MAP_0_START :
        TILE_MAP_1_START;

    for (u8 x = 0; x < DISPLAY_WIDTH; x++)
    {
        // The 256 x 256 pixel
        u8 pixel_y = ly + scy;
        u8 pixel_x = x + scx;

        // The 32 x 32 tile
        u8 tile_y = pixel_y / TILE_HEIGHT;
        u8 tile_x = pixel_x / TILE_WIDTH;

        // The 8 x 8 tile pixel
        u8 tile_pixel_y = pixel_y % TILE_HEIGHT;
        u8 tile_pixel_x = pixel_x % TILE_WIDTH;

        u16 tilemap_index = tile_y * TILE_MAP_WIDTH + tile_x;
        u8 tile_id = mapper.read(tilemap_source + tilemap_index);
        u16 tiledata_address = mapper.memory.lcd_control.address_mode ? 
            TILE_BLOCK_0_START + (tile_id * TILE_SIZE) :
            TILE_BLOCK_1_START + ((static_cast<s8>(tile_id) + 128) * TILE_SIZE);

        tiledata_address += tile_pixel_y * 2;

        u8 lo = mapper.read(tiledata_address);
        u8 hi = mapper.read(tiledata_address + 1);

        u8 color_id = ((lo >> (7 - tile_pixel_x)) & 1) | (((hi >> (7 - tile_pixel_x)) & 1) << 1);
        u8 color = get_color_byte(mapper.memory.palettes.BGP, color_id);

        line[x] = {color_id, color};
    }
    render_queue.push(RenderItem{ly, line, BACKGROUND});
}

void PPU::draw_window_line()
{
    if (!mapper.memory.lcd_control.window_enable || wx > 166) return;
    if (!(wy <= ly && ly < DISPLAY_HEIGHT)) return;

    u8 window_line = internal_ly++;

    u16 tilemap_source = !mapper.memory.lcd_control.window_tile_map ?
        TILE_MAP_0_START :
        TILE_MAP_1_START;
    
    u8 window_pos_y =  window_line;
    if (window_pos_y >= DISPLAY_HEIGHT) return;
    for (u8 x = 0; x < DISPLAY_WIDTH; x++)
    {
        u8 window_pos_x = x + (wx - 7);

        // The 256 x 256 pixel
        u8 pixel_y = window_pos_y;
        u8 pixel_x = x;

        if (window_pos_x >= DISPLAY_WIDTH) continue;

        // The 32 x 32 tile
        u8 tile_y = pixel_y / TILE_HEIGHT;
        u8 tile_x = pixel_x / TILE_WIDTH;

        // The 8 x 8 tile pixel
        u8 tile_pixel_y = pixel_y % TILE_HEIGHT;
        u8 tile_pixel_x = pixel_x % TILE_WIDTH;

        u16 tilemap_index = tile_y * TILE_MAP_WIDTH + tile_x;
        u8 tile_id = mapper.read(tilemap_source + tilemap_index);
        u16 tiledata_address = mapper.memory.lcd_control.address_mode ? 
            TILE_BLOCK_0_START + (tile_id * TILE_SIZE) :
            TILE_BLOCK_1_START + ((static_cast<s8>(tile_id) + 128) * TILE_SIZE);

        tiledata_address += tile_pixel_y * 2;

        u8 lo = mapper.read(tiledata_address);
        u8 hi = mapper.read(tiledata_address + 1);

        u8 color_id = ((lo >> (7 - tile_pixel_x)) & 1) | (((hi >> (7 - tile_pixel_x)) & 1) << 1);
        u8 color = get_color_byte(mapper.memory.palettes.BGP, color_id);

        line[window_pos_x] = {color_id, color};
    }
    render_queue.push(RenderItem{ly, line, WINDOW});
}

void PPU::draw_sprite_line()
{
    if (!mapper.memory.lcd_control.obj_enable) return;

    size_t sprite_size = mapper.memory.lcd_control.obj_size ? TILE_HEIGHT * 2 : TILE_HEIGHT;

    u8 sprite_count = 0;
    for (u8 i = 0; i < mapper.memory.oam.size(); i++)
    {
        if (sprite_count == 10) break;

        const SpriteAttribute &sprite = mapper.memory.oam[i];

        if ((sprite.y_position == 0) || (sprite.y_position >= 160)) continue;
        if ((sprite.x_position == 0) || (sprite.x_position >= 168)) continue;

        u8 pos_y = (sprite.y_position - 16);
        u8 pos_x = (sprite.x_position - 8);
        u8 x_end;
        if ((sprite.x_position - 8) < 0)
        {
            pos_x = 0;
            x_end = 8 - sprite.x_position;
        }
        else
        {
            pos_x = sprite.x_position - 8;
            x_end = 8;
        }

        if (pos_y <= ly && ly < (pos_y + sprite_size))
        {
            u8 pixel_y = ly;
            u8 tile_pixel_y = ly - pos_y;
            u8 y_offset = sprite.y_flip ? 2 * ((sprite_size - 1) - tile_pixel_y) : 2 * tile_pixel_y;
            u8 tile_index = mapper.memory.lcd_control.obj_size ? sprite.tile_index & 0xFE : sprite.tile_index;
            u16 tiledata_address = TILE_BLOCK_0_START + (tile_index * TILE_SIZE);
            tiledata_address += y_offset;
            u8 lo = mapper.read(tiledata_address);
            u8 hi = mapper.read(tiledata_address + 1);

            ColorByte &palette = sprite.palette_number ? mapper.memory.palettes.OBP1 : mapper.memory.palettes.OBP0;

            for (u8 x = 0; x < x_end; x++)
            {
                u8 pixel_x = pos_x + x;
                u8 tile_pixel_x = x;

                u8 x_offset =  sprite.x_flip ? tile_pixel_x : 7 - tile_pixel_x;
                u8 color_id = ((lo >> x_offset) & 1) | (((hi >> x_offset) & 1) << 1);

                u8 color = get_color_byte(palette, color_id);

                if (sprite.BGW && (line[pixel_x].color != 0)) continue;
                line[pixel_x] = {color_id, color};
            }
            render_queue.push(RenderItem{ly, line, SPRITE});
            sprite_count++;
        }
    }
}

u8 PPU::get_color_byte(ColorByte color, u8 index)
{
    switch (index)
    {
        case 0: return color.color_0;
        case 1: return color.color_1;
        case 2: return color.color_2;
        default: return color.color_3;
    }
}

std::string PPU::get_mode_string() const
{
    switch (stat_mode)
    {
        case _0_HBlank: return "HBlank";
        case _1_VBlank: return "VBlank";
        case _2_OAMSearch: return "OAM Search";
        default: return "Draw Line";
    }
}
}