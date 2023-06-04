#include <bitset>
#include <sstream>
#include <cmath>
#include "runner.h"

namespace emulator
{
void Runner::render_debug_panel_1()
{
    ImGui::SetNextWindowPos(ImVec2{2 * ppu.DISPLAY_WIDTH, 0});
    ImGui::SetNextWindowSize(ImVec2{WINDOW_WIDTH - (2 * ppu.DISPLAY_WIDTH), WINDOW_HEIGHT - 300});
    ImGui::Begin("Debug Information", &show_debug_windows, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SeparatorText("CPU Information");
    ImGui::Text("Program Counter: 0x%04x", cpu.get_pc());
    ImGui::Text("Stack Pointer: 0x%04x", cpu.get_sp());
    ImGui::Text("Instruction: 0x%02x 0x%02x 0x%02x 0x%02x", cpu.get_instr(), mapper.read(cpu.get_pc()), mapper.read(cpu.get_pc() + 1), mapper.read(cpu.get_pc() + 2));
    ImGui::Text("Instr. Cycles: %u", cpu.get_instr_cycles());
    ImGui::Text("Total CPU Cycles: %u", cpu.get_total_cycles());

    ImGui::SeparatorText("PPU Information");
    ImGui::Text("Mode: %s", ppu.get_mode_string().c_str());
    ImGui::Text("Address Mode: %u", mapper.memory.lcd_control.address_mode);
    ImGui::Text("BG Tilemap: %u", mapper.memory.lcd_control.bg_tile_map);
    ImGui::Text("Window Tilemap: %u", mapper.memory.lcd_control.window_tile_map);
    ImGui::Text("Render Queue Size: %u", ppu.render_queue.size());
    ImGui::Text("Internal LY: %u", ppu.get_internal_ly());
    ImGui::Text("Mode Cycles: %u", ppu.get_mode_cycles());
    ImGui::Text("Total PPU Cycles: %u", ppu.get_total_cycles());

    ImGui::SeparatorText("App Information");
    ImGui::Text("Total Cycles: %u", cycles);
    ImGui::Text("Average ms/frame: %.3f", 1000.0f / io->Framerate);
    ImGui::Text("FPS: %.1f", io->Framerate);
    ImGui::End();
}

void Runner::render_debug_panel_2()
{
    ImGui::SetNextWindowPos(ImVec2{2 * ppu.DISPLAY_WIDTH, WINDOW_HEIGHT - 300});
    ImGui::SetNextWindowSize(ImVec2{WINDOW_WIDTH - (2 * ppu.DISPLAY_WIDTH) - 180, WINDOW_HEIGHT - 300});
    ImGui::Begin("Register Information", &show_debug_windows, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SeparatorText("Registers");
    ImGui::Text("A: 0x%02X", cpu.get_a());
    ImGui::Text("F: 0x%02X", cpu.get_f());
    ImGui::Text("B: 0x%02X", cpu.get_b());
    ImGui::Text("C: 0x%02X", cpu.get_c());
    ImGui::Text("D: 0x%02X", cpu.get_d());
    ImGui::Text("E: 0x%02X", cpu.get_e());
    ImGui::Text("H: 0x%02X", cpu.get_h());
    ImGui::Text("L: 0x%02X", cpu.get_l());
    ImGui::End();
}

void Runner::render_debug_panel_3()
{
    ImGui::SetNextWindowPos(ImVec2{WINDOW_WIDTH - 180, WINDOW_HEIGHT - 300});
    ImGui::SetNextWindowSize(ImVec2{WINDOW_WIDTH - (2 * ppu.DISPLAY_WIDTH) - 100, WINDOW_HEIGHT - 300});
    ImGui::Begin("External Information", &show_debug_windows, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SeparatorText("LCD Status");
    ImGui::Text("LY: %u", mapper.memory.lcd_status.LY);
    ImGui::Text("LYC: %u", mapper.memory.lcd_status.LYC);
    ImGui::Text("SCX: %u", mapper.memory.lcd_position.SCX);
    ImGui::Text("SCY: %u", mapper.memory.lcd_position.SCY);
    ImGui::Text("WX: %u", mapper.memory.lcd_position.WX);
    ImGui::Text("WY: %u", mapper.memory.lcd_position.WY);
    ImGui::Text("LCD Enable: %u", mapper.memory.lcd_control.lcd_enable);
    ImGui::Text("BG Enable: %u", mapper.memory.lcd_control.bg_enable);
    ImGui::Text("OBJ Enable: %u", mapper.memory.lcd_control.obj_enable);
    ImGui::Text("Window Enable: %u", mapper.memory.lcd_control.window_enable);

    ImGui::SeparatorText("Joypad Status");
    ImGui::Text("Dir. State: 0b%s", std::bitset<4>(joypad.get_direction_keys_state()).to_string().c_str());
    ImGui::Text("Action State: 0b%s", std::bitset<4>(joypad.get_action_keys_state()).to_string().c_str());
    ImGui::End();
}

void Runner::render_debug_panel_4()
{
    ImGui::SetNextWindowPos(ImVec2{0, (2 * ppu.DISPLAY_HEIGHT)});
    ImGui::SetNextWindowSize(ImVec2{160, (WINDOW_HEIGHT - (2 * ppu.DISPLAY_HEIGHT))});
    ImGui::Begin("Register Values", &show_debug_windows, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SeparatorText("Timers");
    ImGui::Text("DIV Timer: 0x%02x", mapper.memory.timer.DIV);
    ImGui::Text("TIMA Timer: 0x%02x", mapper.memory.timer.TIMA);
    ImGui::Text("TMA Value: 0x%02x", mapper.memory.timer.TMA);
    ImGui::Text("Timer Mode: %u", mapper.memory.timer.TAC.mode);
    ImGui::Text("Timer Enable: %u", mapper.memory.timer.TAC.enable);

    ImGui::SeparatorText("Interrupt Flags");
    ImGui::Text("IME: %u", mapper.memory.interrupts.IME);
    ImGui::Text("VBlank: %u(E) %u(F)", mapper.memory.interrupts.IE.vblank, mapper.memory.interrupts.IF.vblank);
    ImGui::Text("LCD Stat: %u(E) %u(F)", mapper.memory.interrupts.IE.lcd_stat, mapper.memory.interrupts.IF.lcd_stat);
    ImGui::Text("Timer: %u(E) %u(F)", mapper.memory.interrupts.IE.timer, mapper.memory.interrupts.IF.timer);
    ImGui::Text("Serial: %u(E) %u(F)", mapper.memory.interrupts.IE.serial, mapper.memory.interrupts.IF.serial);
    ImGui::Text("Joypad: %u(E) %u(F)", mapper.memory.interrupts.IE.joypad, mapper.memory.interrupts.IF.joypad);

    ImGui::SeparatorText("LCD Stat Flags");
    ImGui::Text("LY=LYC: %u", mapper.memory.lcd_status.STAT.lyc_ly);
    ImGui::Text("LY=LYC Source: %u", mapper.memory.lcd_status.STAT.lyc_ly_stat_interrupt);
    ImGui::Text("OAM Source: %u", mapper.memory.lcd_status.STAT.oam_stat_interrupt);
    ImGui::Text("VBlank Source: %u", mapper.memory.lcd_status.STAT.vblank_stat_interrupt);
    ImGui::Text("HBlank Source: %u", mapper.memory.lcd_status.STAT.hblank_stat_interrupt);
    ImGui::End();
}

void Runner::render_debug_panel_5()
{
    static float speed = cycle_speed;
    ImGui::SetNextWindowPos(ImVec2{160, (2 * ppu.DISPLAY_HEIGHT)});
    ImGui::SetNextWindowSize(ImVec2{160, (WINDOW_HEIGHT - (2 * ppu.DISPLAY_HEIGHT))});
    ImGui::Begin("Debug Controls", &show_debug_windows, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    if(ImGui::Button("Pause")) pause = !pause;
    ImGui::SliderFloat("Speed", &speed, 0.0, 1.0, "%.3f");
    cycle_speed = std::pow(speed, 10.0);
    char text[8]{};
    ImGui::InputTextWithHint("(hex)", "address", text, 5);
    std::stringstream stream;
    stream << text;
    u16 value;
    stream >> std::hex >> value;
    for (int i = 0; i < 16; i++) ImGui::Text("0x%04X --> 0x%02X", value + i, mapper.read(value + i));
    ImGui::End();
}
}