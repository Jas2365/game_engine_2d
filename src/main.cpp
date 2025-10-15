#include <Graphics2D.hpp>
#include <Sprite.hpp>
#include <Text.hpp>
#include <Camera2D.hpp>
#include <cmath>
#include <Input.hpp>
#include <Time.hpp>
#include <Colors.hpp>
#include <ball.hpp>

#define window_screen_width     800
#define window_screen_height    600
#define offset_window_width     15
#define offset_window_height    40

screen_t window_screen = { window_screen_width, window_screen_height };
screen_t visible_screen = { window_screen.width - offset_window_width, window_screen.height - offset_window_height };



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR, int){

    color_t blue         = {0, 0, 255 };
    color_t black        = {0, 0, 0 };
    color_t white        = {255, 255, 255 };
    color_t background_c = {1, 1, 15 };

    if(!gfx_init(hInst, window_screen, L"2D Engine")) return 0;

    Input::init();
    Time::init();

    // Camera2D camera;    
    // Text hud(&gfx, L"Consolas", 28.0f);
    // hud.set_color(white);

    circle_t _ball = { visible_screen.width /2,  visible_screen.height /2, 10};
    circle_t _ball_2 = { 13,  13, 10};
    circle_t _ball_3 = { 500,  400, 10};
    rect_t block = { 50, 50, 50, 50};

    pos2_t speed = {500.f, 500.f};

    Ball ball(visible_screen, _ball, color_c::red_c, speed);
    Ball ball_2(visible_screen, _ball_2, color_c::blue_c, speed);
    Ball ball_3(visible_screen, _ball_3, color_c::green_c, speed);
    
    float block_speed = 400.f;

    while(gfx_process_messages()) {
        Time::update();
        float dt = Time::delta_time(); // seconds

        Input::update();

        if(Input::is_key_down(VK_ESCAPE)){
            PostQuitMessage(0);
        }   

        ball.update(dt);
        ball_2.update(dt);
        ball_3.update(dt);
        
        // if(Input::is_key_down(VK_UP)) block.y -= block_speed * dt;
        // if(Input::is_key_down(VK_DOWN)) block.y += block_speed * dt;
        // if(Input::is_key_down(VK_LEFT)) block.x -= block_speed * dt;
        // if(Input::is_key_down(VK_RIGHT)) block.x += block_speed * dt;
      
        gfx_begin_draw();
        gfx_clear(black);

        
        
        ball.draw();
        ball_2.draw();
        ball_3.draw();
        // gfx_fill_rect(block, color_c::gold_c);

        
        gfx_end_draw();
  
    }



    return 0;
}