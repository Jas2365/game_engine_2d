_Pragma("once");

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <string>
#include <stdint.h>
#include <Types.hpp>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

class Graphics2D
{
public:

  static Graphics2D& get();

  bool init(HINSTANCE hInst, screen_t screen, const std::wstring& title);
  bool process_messages();

  void begin_draw();
  void end_draw();

  void clear(color_t &color);
  void set_color(color_t &color);
  
  void draw_line(line_t &line, color_t color, float thickness = 1.f );
  
  void draw_rect(rect_t &rect, color_t color, float thickness = 1.f);
  void fill_rect(rect_t &rect, color_t color);
  
  void draw_circle(circle_t &circle, color_t color, float thickness = 1.f);
  void fill_circle(circle_t &circle, color_t color);
  
  ID2D1Bitmap* load_bitmap(const std::wstring& filename);

  void draw_bitmap_rotated(ID2D1Bitmap* bmp, rect_t &rect, float deg, float scale = 1.f , float opacity =1.f);

  ID2D1HwndRenderTarget* target() const { return m_target; }
  IDWriteFactory* text_factory() const { return m_dwrite_factory; }

private:
  Graphics2D() = default;
  ~Graphics2D();
  Graphics2D(const Graphics2D&) = delete;
  Graphics2D& operator=(const Graphics2D&) = delete;

  HWND m_hwnd                         = nullptr;
  ID2D1Factory* m_factory             = nullptr;
  ID2D1HwndRenderTarget* m_target     = nullptr;
  IWICImagingFactory* m_wic_factory   = nullptr;
  IDWriteFactory* m_dwrite_factory    = nullptr;
  ID2D1SolidColorBrush* m_brush       = nullptr;

  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

inline bool gfx_init(HINSTANCE hInst, screen_t screen, const std::wstring& title){
  return Graphics2D::get().init(hInst, screen, title);
}

inline bool gfx_process_messages(){
  return Graphics2D::get().process_messages();
}

inline void gfx_begin_draw(){
  Graphics2D::get().begin_draw();
}

inline void gfx_end_draw(){
  Graphics2D::get().end_draw();
}

inline void gfx_clear(color_t& color){
  Graphics2D::get().clear(color);
}

inline void gfx_set_color(color_t& color){
  Graphics2D::get().set_color(color);
}

inline void gfx_draw_line(line_t& line, color_t& color, float thickness = 1.0f){
  Graphics2D::get().draw_line(line, color, thickness);
}

inline void gfx_draw_rect(rect_t& rect, color_t& color, float thickness = 1.0f){
  Graphics2D::get().draw_rect(rect, color, thickness);
}

inline void gfx_fill_rect(rect_t& rect, color_t& color){
  Graphics2D::get().fill_rect(rect, color);
}

inline void gfx_draw_circle(circle_t& circle, color_t& color, float thickness = 1.0f){
  Graphics2D::get().draw_circle(circle, color, thickness);
}

inline void gfx_fill_circle(circle_t& circle, color_t& color){
  Graphics2D::get().fill_circle(circle, color);
}

inline ID2D1Bitmap* gfx_load_bitmap(const std::wstring& filename){
  return Graphics2D::get().load_bitmap(filename);
}

inline void gfx_draw_bitmap_rotated(ID2D1Bitmap* bmp, rect_t &rect, float deg, float scale = 1.f , float opacity =1.f){
  Graphics2D::get().draw_bitmap_rotated(bmp, rect, deg, scale, opacity);
}

inline ID2D1HwndRenderTarget* gfx_target() { 
  return Graphics2D::get().target(); 
}

inline IDWriteFactory* gfx_text_factory() {
  return Graphics2D::get().text_factory();
}
