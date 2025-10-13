#include <Sprite.hpp>

Sprite::Sprite(Graphics2D *gfx, const std::wstring &file)
    : m_gfx(gfx), m_bitmap(nullptr)
{
    m_bitmap = gfx->load_bitmap(file);
}

Sprite::~Sprite() {
    if(m_bitmap) m_bitmap->Release();
}

void Sprite::draw(rect_t &_sprite, float rotation, float scale)
{
    m_gfx->draw_bitmap_rotated(m_bitmap, _sprite, rotation, scale);
}
