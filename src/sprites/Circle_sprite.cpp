#include <Circle_sprite.hpp>
#include <Colors.hpp>

#include <pong_constants.hpp>

circle_sprite::circle_sprite(screen_t& screen, circle_t& circle, color_t& color, pos2_t& speed) 
    : m_screen(screen),  m_sprite(circle), m_color(color), m_speed(speed) {}
    
void circle_sprite::draw(){      
    gfx_fill_circle(m_sprite, m_color);
    gfx_draw_circle(m_sprite, color_c::white_c);
}

void circle_sprite::update(float dt, int& player_one_score, int& player_two_score) {
    
    m_sprite.x += m_speed.x * dt;
    m_sprite.y += m_speed.y * dt;
    
    // bounce hor
    if(m_sprite.x - m_sprite.r < 0){
        m_sprite.x = 392;
        m_sprite.y = 280;
        player_two_score++;
        m_speed.x = -m_speed.x;
    }
    
    if(m_sprite.x + m_sprite.r  >= m_screen.width){
        m_sprite.x = 392;
        m_sprite.y = 280;
        player_one_score++;
        m_speed.x = -m_speed.x;
    }

    if(m_sprite.y - m_sprite.r < border_offset + 0){
        m_sprite.y = m_sprite.r + border_offset;
        m_speed.y *= -1;
    }

    if(m_sprite.y + m_sprite.r >= m_screen.height - border_offset){
        m_sprite.y = m_screen.height - m_sprite.r - border_offset;
        m_speed.y *= -1;
    }
}