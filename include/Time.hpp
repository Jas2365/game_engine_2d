_Pragma("once");

#include <windows.h>

class Time {
public:
    static void init();
    static void update();

    static float delta_time(); // seconds since last frame
    static float total_time(); // total time since init seconds

private:
    static LARGE_INTEGER m_frequency;
    static LARGE_INTEGER m_prev;
    static LARGE_INTEGER m_now;

    static float m_delta_time;
    static float m_total_time;
};