#include <Graphics2D.hpp>
#include <Sprite.hpp>
#include <Text.hpp>
#include <Camera2D.hpp>
#include <cmath>
#include <Input.hpp>
#include <Time.hpp>
#include <Colors.hpp>


screen_t window_screen = { 800, 600 };
float offset_window_width = 15;
float offset_window_height = 40;
screen_t visible_screen = { 800 - offset_window_width, 600 - offset_window_height };

class Ball {
private:
    Graphics2D* m_gfx;
    circle_t m_ball;
    color_t m_color;
    pos2_t m_ball_speed = {100.f, 100.f};
    screen_t m_screen;

public:
    Ball(Graphics2D* gfx, screen_t screen, circle_t circle, color_t color) : m_gfx(gfx), m_screen(screen),  m_ball(circle), m_color(color) {}
    
    void draw(){
        m_gfx->fill_circle(m_ball, m_color);
        m_gfx->draw_circle(m_ball, color_c::white_c);
    }

    void update(float dt) {
        
        m_ball.x += m_ball_speed.x * dt;
        m_ball.y += m_ball_speed.y * dt;
        
        // bounce hor
        if(m_ball.x - m_ball.r < 0){
            m_ball.x = m_ball.r;
            m_ball_speed.x *= -1;
        }

        if(m_ball.x + m_ball.r  >= m_screen.width){
            m_ball.x = m_screen.width - m_ball.r;
            m_ball_speed.x *= -1;
        }

        if(m_ball.y - m_ball.r < 0){
            m_ball.y = m_ball.r;
            m_ball_speed.y *= -1;
        }

        if(m_ball.y + m_ball.r >= m_screen.height){
            m_ball.y = m_screen.height - m_ball.r;
            m_ball_speed.y *= -1;
        }

    }

};


int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR, int){
   
    Graphics2D gfx;
    Graphics2D* gfx_p = &gfx;

    color_t blue         = {0, 0, 255 };
    color_t black        = {0, 0, 0 };
    color_t white        = {255, 255, 255 };
    color_t background_c = {1, 1, 15 };

    if(!gfx.init(hInst, window_screen, L"2D Engine")) return 0;

    Input::init();
    Time::init();

    Camera2D camera;    
    // Text hud(&gfx, L"Consolas", 28.0f);
    // hud.set_color(white);

    circle_t _ball = { visible_screen.width /2,  visible_screen.height /2, 10};
    rect_t block = { 50, 50, 50, 50};

    Ball ball(gfx_p, visible_screen, _ball, color_c::blue_c);

    float block_speed = 400.f;

    while(gfx.process_messages()) {
        Time::update();
        float dt = Time::delta_time(); // seconds

        Input::update();

        if(Input::is_key_down(VK_ESCAPE)){
            PostQuitMessage(0);
        }   

        ball.update(dt);
        
        // if(Input::is_key_down(VK_UP)) block.y -= block_speed * dt;
        // if(Input::is_key_down(VK_DOWN)) block.y += block_speed * dt;
        // if(Input::is_key_down(VK_LEFT)) block.x -= block_speed * dt;
        // if(Input::is_key_down(VK_RIGHT)) block.x += block_speed * dt;
      
        gfx.begin_draw();
        gfx.clear(black);

        
        
        ball.draw();
        // gfx.fill_rect(block, color_c::gold_c);

        
        gfx.end_draw();
  
    }



    return 0;
}