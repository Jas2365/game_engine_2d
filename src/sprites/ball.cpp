#include <ball.hpp>
#include <Colors.hpp>

Ball::Ball(screen_t& screen, circle_t& circle, color_t& color, pos2_t& speed) 
    : m_screen(screen),  m_ball(circle), m_color(color), m_speed(speed) {}
    
void Ball::draw(){      
    gfx_fill_circle(m_ball, m_color);
    gfx_draw_circle(m_ball, color_c::white_c);
}

void Ball::update(float dt) {
    
    m_ball.x += m_speed.x * dt;
    m_ball.y += m_speed.y * dt;
    
    // bounce hor
    if(m_ball.x - m_ball.r < 0){
        m_ball.x = m_ball.r;
        m_speed.x *= -1;
    }

    if(m_ball.x + m_ball.r  >= m_screen.width){
        m_ball.x = m_screen.width - m_ball.r;
        m_speed.x *= -1;
    }

    if(m_ball.y - m_ball.r < 0){
        m_ball.y = m_ball.r;
        m_speed.y *= -1;
    }

    if(m_ball.y + m_ball.r >= m_screen.height){
        m_ball.y = m_screen.height - m_ball.r;
        m_speed.y *= -1;
    }
}