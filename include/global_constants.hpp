_Pragma("once");

#include <Types.hpp>

#define window_screen_width     800
#define window_screen_height    600
#define offset_window_width     15
#define offset_window_height    40

screen_t static  window_screen = { window_screen_width, window_screen_height };
screen_t static visible_screen = { window_screen.width - offset_window_width, window_screen.height - offset_window_height };
