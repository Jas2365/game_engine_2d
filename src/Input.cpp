#include <Input.hpp>

std::array<bool, 256> Input::m_keys = { false };
std::array<bool, 256> Input::m_prev_keys = { false };

void Input::init() 
{
    m_keys.fill(false);
    m_prev_keys.fill(false);
  
}

void Input::update() {
    m_prev_keys = m_keys;
    for(int i = 0; i< 256; ++i){
        m_keys[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
    }

}

bool Input::is_key_down(key_t key) {
    return m_keys[key];
}

bool Input::is_key_pressed(key_t key) {
    return m_keys[key] && !m_prev_keys[key];
}

bool Input::is_key_released(key_t key) {
    return !m_keys[key] && m_prev_keys[key];
}
