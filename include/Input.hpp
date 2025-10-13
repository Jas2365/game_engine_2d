_Pragma("once");

#include <windows.h>
#include <array>
#include <Types.hpp>


class Input {
public:
    static void init();
    static void update();

    // keyboard
    static bool is_key_down(key_t key);
    static bool is_key_pressed(key_t key);
    static bool is_key_released(key_t key);

private:
    static std::array<bool, 256> m_keys;
    static std::array<bool, 256> m_prev_keys;

};