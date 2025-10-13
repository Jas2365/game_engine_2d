_Pragma("once");

#include <Graphics2D.hpp>

class Text {
public:
    Text(Graphics2D* gfx, const std::wstring& font_family, float font_size);
    ~Text();

    void set_color(color_t &color);
    void draw(const std::wstring& text, rect_t& text_container);

private:
    Graphics2D* m_gfx;
    IDWriteTextFormat* m_format = nullptr; 
    ID2D1SolidColorBrush* m_brush = nullptr;
};