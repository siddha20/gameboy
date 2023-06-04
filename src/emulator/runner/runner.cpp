#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include "runner.h"

namespace emulator
{
Runner::Runner(const std::string &rom_file_name)
    : mapper{}
    , cpu{mapper}
    , ppu{mapper}
    , joypad{mapper}
    , cycles{}
    , show_debug_windows{true}
    , pause{false}
{
    // Load ROM into memory.
    std::ifstream in(rom_file_name, std::ios::binary);
    std::vector<char> ROM((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    mapper.cartridge.load_rom(ROM);

    init_sdl();
    init_imgui();
}

Runner::~Runner()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Runner::start()
{
    bool done = false;
    u64 start_tick = 0, end_tick = 0, delta_tick;
    while (!done)
    {
        start_tick = SDL_GetTicks64();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) done = true;
            if (event.type == SDL_WINDOWEVENT && 
                event.window.event == SDL_WINDOWEVENT_CLOSE && 
                event.window.windowID == SDL_GetWindowID(window)) done = true;
        }

        joypad.update();

        if (!pause)
        {
            for (int i = 0; i < 70224 ; i++)
            {
                if (cycles % 4 == 0) cpu.step();
                ppu.step();
                ++cycles;
            }
        }

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        render_debug_panel_1();
        render_debug_panel_2();
        render_debug_panel_3();
        render_debug_panel_4();
        render_debug_panel_5();

        ImGui::Render();
        SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);

        render_ppu_line_queue();

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);

        end_tick = SDL_GetTicks64();
        delta_tick = end_tick - start_tick;
        if(delta_tick < (1000.0 / (60.0))) SDL_Delay((1000.0 / (60.0)) - delta_tick);
    }
}

void Runner::init_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        std::cerr << "Error intializing SDL: " << SDL_GetError() << std::endl;
    }
    window = SDL_CreateWindow("Gameboy Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) std::cerr << "Could not create renderer" << std::endl;
}

void Runner::init_imgui()
{
    ImGui::CreateContext();
    ImGuiIO &io_ref = ImGui::GetIO();
    io = &io_ref;
    io->IniFilename = NULL;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void Runner::render_ppu_line_queue()
{
    while (ppu.render_queue.size() != 0)
    {
        PPU::RenderItem item{ppu.render_queue.front()};
        ppu.render_queue.pop();
        for (int i = 0; i < item.data.size(); i++)
        {
            if ((item.line_type == PPU::SPRITE) && (item.data[i].id == 0)) continue;
            int window_pos_x = i;
            int window_pos_y = item.line;
            if (window_pos_x >= ppu.DISPLAY_WIDTH || window_pos_y >= ppu.DISPLAY_HEIGHT) continue;
            set_color(item.data[i].color, 255);
            SDL_Rect rect{2 * window_pos_x, 2 * window_pos_y, 2, 2};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Runner::set_color(u8 id, u8 alpha)
{
    switch (id)
    {
        case 0: SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha); break;
        case 1: SDL_SetRenderDrawColor(renderer, 170, 170, 170, alpha); break;
        case 2: SDL_SetRenderDrawColor(renderer, 85, 85, 85, alpha); break;
        case 3: SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha); break;    
    }
}
}