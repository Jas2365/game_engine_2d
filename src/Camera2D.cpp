#include "Camera2D.hpp"

Camera2D::Camera2D() 
    : m_cam_pos({0,0}), m_zoom(1.0f), m_rotation_deg(0) {}

void Camera2D::set_positon(float x, float y) {
    m_cam_pos.x = x;
    m_cam_pos.y = y;
}

void Camera2D::move(float x, float y) {
    m_cam_pos.x += x;
    m_cam_pos.y += y;
}

void Camera2D::set_zoom(float zoom) {
    if(zoom < 0.1f) zoom=0.1f;
    m_zoom = zoom;
}

void Camera2D::set_rotation(float rotation_deg) {
    m_rotation_deg = rotation_deg;
}

void Camera2D::apply(ID2D1RenderTarget *target, screen_t screen) {
    // reset to identity
    target->SetTransform(D2D1::Matrix3x2F::Identity());

    // camera transform:  translate -> rotate -> scale -> center
    D2D1_MATRIX_3X2_F transform = 
            D2D1::Matrix3x2F::Translation(-m_cam_pos.x, -m_cam_pos.y) *
            D2D1::Matrix3x2F::Rotation(m_rotation_deg, D2D1::Point2F(m_cam_pos.x,m_cam_pos.y)) *
            D2D1::Matrix3x2F::Scale(
                                    m_zoom, m_zoom, 
                                    D2D1::Point2F(screen.width /2, screen.height /2)   
                                )*
            D2D1::Matrix3x2F::Translation(screen.width /2, screen.height /2);
    target->SetTransform(transform);
}

void Camera2D::reset(ID2D1RenderTarget *target) {
    target->SetTransform(D2D1::Matrix3x2F::Identity());
}
