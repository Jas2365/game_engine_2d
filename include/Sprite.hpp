_Pragma("once");

#include <Graphics2D.hpp>

class Sprite {  
public:
    Sprite(Graphics2D* gfx, const std::wstring& file);
    ~Sprite();
    void draw(rect_t& _sprite, float rotation = 0.0f, float scale = 1.0f);

private:
    Graphics2D* m_gfx;
    ID2D1Bitmap* m_bitmap;
};