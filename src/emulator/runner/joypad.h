#pragma once
#include <map>
#include <utility>
#include "mapper.h"
#include "memory.h"
#include "imgui.h"

namespace emulator
{
class Joypad
{
enum KeyType
{
    DIRECTION,
    ACTION
};

enum KeyLabel
{
    RIGHT = 0,
    LEFT = 1,
    UP = 2,
    DOWN = 3,
    A = 0,
    B = 1,
    SELECT = 2,
    START = 3
};

public:
    static constexpr ImGuiKey UP_KEY = ImGuiKey_W;
    static constexpr ImGuiKey DOWN_KEY = ImGuiKey_S;
    static constexpr ImGuiKey RIGHT_KEY = ImGuiKey_D;
    static constexpr ImGuiKey LEFT_KEY = ImGuiKey_A;
    static constexpr ImGuiKey A_KEY = ImGuiKey_K;
    static constexpr ImGuiKey B_KEY = ImGuiKey_J;
    static constexpr ImGuiKey SELECT_KEY = ImGuiKey_N;
    static constexpr ImGuiKey START_KEY = ImGuiKey_M;

    Joypad(Mapper &mapper);

    static u8 get_joypad_state(JoypadStatus joypad_status, JoypadState joypad_state);
    u8 get_direction_keys_state() const { return direction_keys_state & 0x0F; }
    u8 get_action_keys_state() const { return action_keys_state & 0x0F; }
    void reset() { direction_keys_state = 0x0F; action_keys_state = 0x0F; }
    void update();

private:
    Mapper &mapper;
    JoypadStatus &joypad;
    u8 &joypad_out;
    u8 &direction_keys_state;
    u8 &action_keys_state;
    std::map<ImGuiKey, std::pair<KeyType, KeyLabel>> key_map;
};
}