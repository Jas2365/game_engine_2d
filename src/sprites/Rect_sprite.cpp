#include <Rect_sprite.hpp>

#include <Colors.hpp>
#include <Input.hpp>

#include <pong_constants.hpp>

rect_sprite::rect_sprite(screen_t &screen, rect_t& rect, color_t& color, float speed) 
    : m_screen(screen), m_sprite(rect), m_color(color), m_speed(speed) {}

void rect_sprite::draw() {

    gfx_fill_rect(m_sprite, m_color);
    gfx_draw_rect(m_sprite, color_c::white_c);

}

void rect_sprite::update(float dt, int up_key, int down_key) {
       
    if(Input::is_key_down(up_key)) m_sprite.y -= m_speed * dt;
    if(Input::is_key_down(down_key)) m_sprite.y += m_speed * dt;

    if ( m_sprite.y <= 0 + border_offset ) {
        m_sprite.y = 0 + border_offset;
    }
    if ( m_sprite.y + m_sprite.h >= m_screen.height - border_offset ) {
        m_sprite.y = m_screen.height - border_offset - m_sprite.h;
    }

}
