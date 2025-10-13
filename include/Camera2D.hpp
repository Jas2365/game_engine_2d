_Pragma("once");

#include <d2d1.h>
#include <Types.hpp>
class Camera2D
{
public:
    Camera2D();

    void set_positon(float x, float y);
    void move(float x, float y);
    void set_zoom(float zoom);
    void set_rotation(float rotation_deg);

    void apply(ID2D1RenderTarget* target, screen_t screen);
    void reset(ID2D1RenderTarget* target);

    inline float x() const { return m_cam_pos.x; }
    inline float y() const { return m_cam_pos.y; }
    inline float zoom() const {return m_zoom; }
    inline float rotation_deg() const {return m_rotation_deg; }
    

private:
    pos2_t m_cam_pos;
    float m_zoom;
    float m_rotation_deg;
};
