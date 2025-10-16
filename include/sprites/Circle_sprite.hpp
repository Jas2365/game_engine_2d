_Pragma("once");

#include <Graphics2D.hpp>

class circle_sprite {
    
public:
    circle_t m_sprite;
    pos2_t m_speed;

    circle_sprite(screen_t &screen, circle_t &circle, color_t &color, pos2_t &speed);
    void draw();
    void update(float dt, int& player_one_score, int& player_two_score);
    
private:
    color_t m_color;
    screen_t m_screen;
};
