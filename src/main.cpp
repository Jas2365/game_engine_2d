#include <Graphics2D.hpp>
#include <Sprite.hpp>
#include <Text.hpp>
#include <Camera2D.hpp>
#include <cmath>
#include <Input.hpp>
#include <Time.hpp>
#include <Colors.hpp>
#include <ball.hpp>

#include <global_constants.hpp>


int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR, int){


    if(!gfx_init(hInst, window_screen, L"2D Engine")) return 0;

    Input::init();
    Time::init();

    circle_t _ball   = { 10 , 500 , 10};
    circle_t _ball_2 = { 13 ,  13 , 10};
    circle_t _ball_3 = { 500, 400 , 10};


    pos2_t speed = {500.f, 500.f};

    Ball ball  (visible_screen, _ball  , color_c::red_c,   speed);
    Ball ball_2(visible_screen, _ball_2, color_c::blue_c,  speed);
    Ball ball_3(visible_screen, _ball_3, color_c::green_c, speed);
    
    float block_speed = 400.f;

    while(gfx_process_messages()) {
        Time::update();
        Input::update();

        float dt = Time::delta_time(); // seconds


        if(Input::is_key_down(VK_ESCAPE)){
            // Quit window message
            PostQuitMessage(0);
        }   

        ball.  update(dt);
        ball_2.update(dt);
        ball_3.update(dt);
        
        gfx_begin_draw();

        gfx_clear(color_c::black_c);
        
        ball.  draw();
        ball_2.draw();
        ball_3.draw();
        
        gfx_end_draw();
  
    }

    return 0;
}