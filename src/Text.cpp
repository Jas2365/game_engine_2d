#include <Text.hpp>

Text& Text::get() {
    static Text instance;
    return instance;
}

void Text::init(const std::wstring &font_family, float font_size) 
{

    Graphics2D::get().text_factory()->CreateTextFormat(
        font_family.c_str(),
        nullptr, 
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        font_size,
        L"en-us",
        &m_format
    );

    Graphics2D::get().target()->CreateSolidColorBrush(
        D2D1::ColorF(1,1,1),
        &m_brush
    );
}

Text::~Text() {
    if(m_brush) m_brush->Release();
    if(m_format) m_format->Release();
}

void Text::set_color(color_t &color) {
    m_brush->SetColor(D2D1::ColorF(color.r, color.g, color.b));
}

void Text::draw(const std::wstring &text, rect_t &text_container) {
    D2D1_RECT_F layout = D2D1::RectF(
                                    text_container.x, 
                                    text_container.y,
                                    text_container.x + text_container.w, 
                                    text_container.y + text_container.h
                                );
    
    Graphics2D::get().target()->DrawTextW(
                            text.c_str(),
                            (UINT32)text.size(),
                            m_format,
                            layout,
                            m_brush
                        );
}
