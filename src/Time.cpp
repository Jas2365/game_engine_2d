#include "Time.hpp"

LARGE_INTEGER Time::m_frequency;
LARGE_INTEGER Time::m_prev;
LARGE_INTEGER Time::m_now;

float Time::m_delta_time = 0.0f;
float Time::m_total_time = 0.0f;

void Time::init() {
    QueryPerformanceFrequency(&m_frequency);
    QueryPerformanceCounter(&m_prev);

    m_total_time = 0.f;
    m_delta_time = 0.f;
}

void Time::update() {
    QueryPerformanceCounter(&m_now);
    m_delta_time = float(m_now.QuadPart - m_prev.QuadPart) / float(m_frequency.QuadPart);
    m_total_time += m_delta_time;
    m_prev = m_now;
}

float Time::delta_time()
{
    return m_delta_time;
}

float Time::total_time()
{
    return m_total_time;
}
