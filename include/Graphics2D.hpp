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
  Graphics2D();
  ~Graphics2D();

  bool init(HINSTANCE hInst, int width, int height, const std::wstring& title);
  bool process_messages();

  void begin_draw();
  void end_draw();

  void clear(color_t &color);
  void set_color(color_t &color);
  
  void draw_line(line_t &line, float thickness = 1.f );
  
  void draw_rect(rect_t &rect, float thickness = 1.f);
  void fill_rect(rect_t &rect);
  
  void draw_circle(circle_t &circle, float thickness = 1.f);
  void fill_circle(circle_t &circle);
  
  ID2D1Bitmap* load_bitmap(const std::wstring& filename);

  void draw_bitmap_rotated(ID2D1Bitmap* bmp, rect_t &rect, float deg, float scale = 1.f , float opacity =1.f);

  ID2D1HwndRenderTarget* target() const { return m_target; }
  IDWriteFactory* text_factory() const { return m_dwrite_factory; }

  inline HWND window() { return m_hwnd; }
private:
  HWND m_hwnd                         = nullptr;
  ID2D1Factory* m_factory             = nullptr;
  ID2D1HwndRenderTarget* m_target     = nullptr;
  IWICImagingFactory* m_wic_factory   = nullptr;
  IDWriteFactory* m_dwrite_factory    = nullptr;
  ID2D1SolidColorBrush* m_brush       = nullptr;

  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};


