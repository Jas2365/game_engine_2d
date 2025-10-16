#include <Graphics2D.hpp>
#include <Input.hpp>

#include <cstdint>
#include <cstring>
#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include <cassert>

Graphics2D& Graphics2D::get() {
    static Graphics2D instance;
    return instance;
}

void Graphics2D::shutdown()
{
    
    if(m_brush) {
        m_brush->Release(); 
        m_brush = nullptr;  
    }
    if(m_target) {
        m_target->Release(); 
        m_target = nullptr;  
    }
    if(m_factory) {
        m_factory->Release(); 
        m_factory = nullptr;  
    }
    if(m_wic_factory) {
        m_wic_factory->Release(); 
        m_wic_factory = nullptr;  
    }
    if(m_dwrite_factory) {
        m_dwrite_factory->Release(); 
        m_dwrite_factory = nullptr;  
    }
    if(m_hwnd) m_hwnd = nullptr; 
}

Graphics2D::~Graphics2D()
{
    if(m_brush) m_brush->Release();
    if(m_target) m_target->Release();
    if(m_factory) m_factory->Release();
    if(m_wic_factory) m_wic_factory->Release();
    if(m_dwrite_factory) m_dwrite_factory->Release();
    if(m_hwnd) m_hwnd = nullptr; 
}

LRESULT CALLBACK Graphics2D::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    if(msg == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

bool Graphics2D::init(HINSTANCE hInst, screen_t screen, const std::wstring &title)
{
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"Game_Window";
    RegisterClassW(&wc);

    m_hwnd = CreateWindowExW(0,
                            wc.lpszClassName, 
                            title.c_str(),
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            screen.width, screen.height, 
                            nullptr, nullptr,
                            hInst,
                            nullptr    
                        );

    if(!m_hwnd) return false;

    ShowWindow(m_hwnd, SW_SHOW);
    
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);

    if(FAILED(hr)) return false;
    
    RECT rc; GetClientRect(m_hwnd, &rc);
    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    hr = m_factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hwnd, size),
        &m_target
    );
    
    if(FAILED(hr)) return false;
    
    hr = CoCreateInstance(
        CLSID_WICImagingFactory, 
        nullptr, 
        CLSCTX_INPROC_SERVER, 
        IID_PPV_ARGS(&m_wic_factory)
    );
    
    if(FAILED(hr)) return false;


    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_dwrite_factory));
    if(FAILED(hr)) return false;

    m_target->CreateSolidColorBrush(D2D1::ColorF(1,1,1), &m_brush);

    return true;
}

bool Graphics2D::process_messages()
{
    MSG msg = {};
    while(PeekMessageW(&msg, nullptr, 0,0, PM_REMOVE)){
        if(msg.message == WM_QUIT)return false;
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return true;
}

void Graphics2D::begin_draw() {
    // m_target->SetTransform(D2D1::Matrix3x2F::Identity());
    m_target->BeginDraw();
}

void Graphics2D::end_draw() {
    m_target->EndDraw();
}

void Graphics2D::clear(color_t &color)
{
    m_target->Clear(D2D1::ColorF(color.r, color.g, color.b));
}

void Graphics2D::set_color(color_t &color)
{
    m_brush->SetColor(D2D1::ColorF(color.r, color.g, color.b));
}

void Graphics2D::draw_line(line_t &line, color_t color, float thickness)
{
    auto old_color =  m_brush->GetColor();
    m_brush->SetColor(D2D1::ColorF(color.r, color.g, color.b));
    m_target->DrawLine(
                D2D1::Point2F(
                    line.x1, 
                    line.y1
                ),
                D2D1::Point2F(
                    line.x2, 
                    line.y2
                ), 
                m_brush, 
                thickness
            );
    m_brush->SetColor(old_color);
}

void Graphics2D::draw_rect(rect_t &rect, color_t color, float thickness)
{
    auto old_color =  m_brush->GetColor();
    m_brush->SetColor(D2D1::ColorF(color.r, color.g, color.b));
    m_target->DrawRectangle(
                D2D1::RectF(
                    rect.x, 
                    rect.y, 
                    rect.x + rect.w, 
                    rect.y + rect.h
                ), 
                m_brush, 
                thickness
            );   
    m_brush->SetColor(old_color);
}

void Graphics2D::fill_rect(rect_t &rect, color_t color)
{
    auto old_color =  m_brush->GetColor();
    m_brush->SetColor(D2D1::ColorF(color.r, color.g, color.b));
    
    m_target->FillRectangle(
                D2D1::RectF(
                    rect.x,
                    rect.y,
                    rect.x + rect.w,
                    rect.y + rect.h
                ),
                m_brush
            );
    m_brush->SetColor(old_color);
}

void Graphics2D::draw_circle(circle_t &circle, color_t color, float thickness)
{
    auto old_color =  m_brush->GetColor();
    m_brush->SetColor(D2D1::ColorF(color.r, color.g, color.b));
    
    m_target->DrawEllipse(
                D2D1::Ellipse(
                    D2D1::Point2F(
                        circle.x, 
                        circle.y
                    ),
                    circle.r, 
                    circle.r
                ),
                m_brush, 
                thickness
            );
    m_brush->SetColor(old_color);
}

void Graphics2D::fill_circle(circle_t &circle, color_t color)
{
    auto old_color =  m_brush->GetColor();
    m_brush->SetColor(D2D1::ColorF(color.r, color.g, color.b));
    
    m_target->FillEllipse(
                D2D1::Ellipse(
                    D2D1::Point2F(
                        circle.x, 
                        circle.y
                    ),
                    circle.r, 
                    circle.r
                ),
                m_brush
            );
    m_brush->SetColor(old_color);
}

ID2D1Bitmap *Graphics2D::load_bitmap(const std::wstring &filename)
{
    IWICBitmapDecoder* decoder = nullptr;
    IWICBitmapFrameDecode* frame = nullptr;
    IWICFormatConverter* converter = nullptr;
    ID2D1Bitmap* bmp = nullptr;
    
    HRESULT hr = m_wic_factory->CreateDecoderFromFilename(
                                    filename.c_str(),
                                    nullptr,
                                    GENERIC_READ,
                                    WICDecodeMetadataCacheOnLoad,
                                    &decoder
                                );
    
    if(FAILED(hr)) return nullptr;

    decoder->GetFrame(0, &frame);

    m_wic_factory->CreateFormatConverter(&converter);
    converter->Initialize(
                    frame, 
                    GUID_WICPixelFormat32bppPBGRA,
                    WICBitmapDitherTypeNone, 
                    nullptr,
                    0.0f,
                    WICBitmapPaletteTypeCustom
                );
    m_target->CreateBitmapFromWicBitmap(converter, nullptr, &bmp);

    if(decoder) decoder->Release();
    if(frame) frame->Release();
    if(converter) converter->Release();
    
    return bmp;
}

void Graphics2D::draw_bitmap_rotated(ID2D1Bitmap *bmp, rect_t &rect, float deg, float scale, float opacity)
{
    if(!bmp) return;

    D2D1_MATRIX_3X2_F old_transform;
    m_target->GetTransform(&old_transform);

    D2D1_POINT_2F center = D2D1::Point2F(
                                    rect.x + ( rect.w * scale) / 2.f,
                                    rect.y + ( rect.h * scale) / 2.f
                                );

    D2D1_MATRIX_3X2_F transform = 
        D2D1::Matrix3x2F::Translation(-rect.w / 2, -rect.h / 2) 
        *
        D2D1::Matrix3x2F::Rotation(deg, D2D1::Point2F(0,0))
        * 
        D2D1::Matrix3x2F::Scale(scale, scale) 
        * 
        D2D1::Matrix3x2F::Translation(center.x, center.y); 

    m_target->SetTransform(transform);
    m_target->DrawBitmap(bmp, D2D1::RectF(0,0, rect.w, rect.h), opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    m_target->SetTransform(old_transform);
}

