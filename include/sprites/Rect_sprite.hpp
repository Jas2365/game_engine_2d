_Pragma("once");

#include <Graphics2D.hpp>

class rect_sprite {

public:
    rect_t m_sprite;
    float m_speed;

    rect_sprite(screen_t &screen, rect_t& rect, color_t& color, float speed);
    void draw();
    void update(float dt, int up_key, int down_key);


private:
    color_t m_color;
    screen_t m_screen;
};
