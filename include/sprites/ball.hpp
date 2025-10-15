_Pragma("once");

#include <Graphics2D.hpp>

class Ball {
    
public:
    Ball(screen_t &screen, circle_t &circle, color_t &color, pos2_t &speed);
    
    void draw();
    void update(float dt);
    
private:
    circle_t m_ball;
    color_t m_color;
    pos2_t m_speed;
    screen_t m_screen;
};
