#include "joypad.h"
#include <bitset>

namespace emulator
{
Joypad::Joypad(Mapper &mapper)
    : mapper{mapper}
    , joypad{mapper.memory.joypad}
    , joypad_out{mapper.memory.joypad_out}
    , direction_keys_state{mapper.memory.joypad_state.direction_keys_state}
    , action_keys_state{mapper.memory.joypad_state.action_keys_state} 
    , key_map{}
{
    key_map[UP_KEY] = {DIRECTION, UP};
    key_map[DOWN_KEY] = {DIRECTION, DOWN};
    key_map[RIGHT_KEY] = {DIRECTION, RIGHT};
    key_map[LEFT_KEY] = {DIRECTION, LEFT};
    key_map[A_KEY] = {ACTION, A};
    key_map[B_KEY] = {ACTION, B};
    key_map[SELECT_KEY] = {ACTION, SELECT};
    key_map[START_KEY] = {ACTION, START};
}

void Joypad::update()
{
    for (auto &[key, value] : key_map)
    {
        const auto [type, label] = value;
        bool status = ImGui::IsKeyDown(key);
        switch (type)
        {
            case DIRECTION: set_bit(direction_keys_state, label, !status); break;
            case ACTION: set_bit(action_keys_state, label, !status); break;
        }
        if (!status) mapper.memory.interrupts.IF.joypad = 1;
    }
}

u8 Joypad::get_joypad_state(JoypadStatus joypad_status, JoypadState joypad_state)
{
    u8 result = 0x0F;
    if (!joypad_status.direction_keys) result &= joypad_state.direction_keys_state;
    if (!joypad_status.button_keys) result &= joypad_state.action_keys_state;
    return (joypad_status.flag_byte & 0xF0) | (result & 0x0F);
}
}