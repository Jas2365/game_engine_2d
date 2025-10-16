_Pragma("once");

#include <Graphics2D.hpp>

class Text {
public:
    static Text& get();
    
    void init(const std::wstring& font_family, float font_size);
    void set_color(color_t &color);
    void draw(const std::wstring& text, rect_t& text_container);
    
private:
    Text() = default;
    ~Text();
    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;
   
    IDWriteTextFormat* m_format = nullptr; 
    ID2D1SolidColorBrush* m_brush = nullptr;
};

inline void gfx_draw_text(const std::wstring& text, rect_t& text_container, color_t& font_color){
    Text::get().set_color(font_color);
    Text::get().draw(text, text_container);
}
