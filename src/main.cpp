#include <Graphics2D.hpp>
#include <Sprite.hpp>
#include <Text.hpp>
#include <cmath>
#include <Input.hpp>
#include <Time.hpp>
#include <Colors.hpp>

#include <Circle_sprite.hpp>
#include <Rect_sprite.hpp>
#include <Collisions.hpp>

#include <global_constants.hpp>


int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR, int){


    if(!gfx_init(hInst, window_screen, L"Pong game")) return 0;

    Text::get().init(L"Consolas", 50.0f);

    Input::init();
    Time::init();

    circle_t _ball   = { 10 , 500 , 10};

    rect_t _player_one = {750, 250, 20, 100};
    rect_t _player_two = { 15, 250, 20, 100};
    
    pos2_t ball_speed = {450.f, 450.f};
    float player_speed = 500.f;
    
    rect_t player_one_score_container = {200, 40, 60, 60};
    rect_t player_two_score_container = {500, 40, 60, 60};

    line_t middle_net   = { 392.0f  , 0.0f     , 392.0f   , 560.0f };
    line_t left_wall    = { 0.0f    , 0.0f     , 0.0f     , 560.0f };
    line_t right_wall   = { 785.0f  , 0.0f     , 785.0f   , 560.0f };
    line_t top_wall     = { 0.0f    , 0.0f     , 785.0f   , 0.0f   };
    line_t down_wall    = { 0.0f    , 560.0f   , 785.0f   , 560.0f };

    circle_sprite ball       (visible_screen , _ball       , color_c::red_c         , ball_speed    );
    rect_sprite   player_one (visible_screen , _player_one , color_c::blue_violet_c , player_speed  );
    rect_sprite   player_two (visible_screen , _player_two , color_c::dark_violet_c , player_speed  );

    int player_one_score = 0;
    int player_two_score = 0;

    while(gfx_process_messages()) {
        Time::update();
        Input::update();

        float dt = Time::delta_time(); // seconds


        if(Input::is_key_down(VK_ESCAPE)){
            // Quit window message
            PostQuitMessage(0);
        }   

        // sprite updates
        ball        .update(dt, player_one_score, player_two_score);
        player_one  .update(dt, VK_UP, VK_DOWN);
        player_two  .update(dt, 'W', 'S');

        // collision
        if(collide_circle_rect(ball.m_sprite, player_one.m_sprite)){
            ball.m_sprite.x = player_one.m_sprite.x - ball.m_sprite.r;
            ball.m_speed.x = -ball.m_speed.x;

        }        
        if(collide_circle_rect(ball.m_sprite, player_two.m_sprite)){
            ball.m_sprite.x = player_two.m_sprite.x + player_two.m_sprite.w + ball.m_sprite.r;
            ball.m_speed.x = -ball.m_speed.x;
        }        


        gfx_begin_draw();

        gfx_clear(color_c::black_c);
        
        // background 
        gfx_draw_line( middle_net , color_c::aquamarine_c , 24.f );
        gfx_draw_line( left_wall  , color_c::aquamarine_c , 12.f );
        gfx_draw_line( right_wall , color_c::aquamarine_c , 12.f );
        gfx_draw_line( top_wall   , color_c::aquamarine_c , 12.f );
        gfx_draw_line( down_wall  , color_c::aquamarine_c , 12.f );

        // sprites
        ball        .draw();
        player_one  .draw();
        player_two  .draw();

        // scores
        gfx_draw_text(
            std::to_wstring(player_one_score),
            player_one_score_container,
            color_c::alice_blue_c
        );
        gfx_draw_text(
            std::to_wstring(player_two_score),
            player_two_score_container,
            color_c::alice_blue_c
        );

        gfx_end_draw();
  
    }

    gfx_shutdown();

    return 0;

}