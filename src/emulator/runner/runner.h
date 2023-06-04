#pragma once
#include <string>
#include "cpu.h"
#include "ppu.h"
#include "joypad.h"
#include "common.h"
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

namespace emulator
{
class Runner
{
public:
    static constexpr size_t WINDOW_HEIGHT = 650;
    static constexpr size_t WINDOW_WIDTH = 600;
    static constexpr int PIXEL_SCALE = 2;
    static constexpr double FRAME_RATE = 60;
    static constexpr u64 DOTS_PER_FRAME = 70224;

    Runner(const std::string& rom_file_name);
    ~Runner();

    void start();

private:
    Mapper mapper;
    CPU cpu;
    PPU ppu;
    Joypad joypad;
    u64 cycles;
    SDL_Window* window;
    SDL_Renderer* renderer;
    ImGuiIO *io;
    bool show_debug_windows;
    bool pause;
    float cycle_speed;

    void init_sdl();
    void init_imgui();
    void set_color(u8 id, u8 alpha);
    void render_ppu_line_queue();
    void render_debug_panel_1();
    void render_debug_panel_2();
    void render_debug_panel_3();
    void render_debug_panel_4();
    void render_debug_panel_5();

    friend void runner_tests();
};
}