#include <Graphics2D.hpp>
#include <Sprite.hpp>
#include <Text.hpp>
#include <Camera2D.hpp>
#include <cmath>
#include <Input.hpp>

screen_t screen = { 800, 600 };

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR, int){
   
    Graphics2D gfx;

    color_t blue = { 0, 0, 255.f };
    color_t black = { 0, 0, 0 };
    color_t background_c = { 0.1f, 0.1f, 0.15f };

    rect_t camera_x_rect = {10,10,300,30};
    rect_t camera_y_rect = {10,40,300,30};
    rect_t zoom_rect = {10,70,300,30};

    if(!gfx.init(hInst, screen.width, screen.height, L"2D Engine")) return 0;

    Input::init();

    Sprite brown_ball(&gfx, L"assets/sprite_ball_brown.png");
    Text hud(&gfx, L"Consolas", 28.0f);
    Camera2D camera;    

    rect_t _brown_ball_coords = {300, 200, 128, 128};

    rect_t block = { 100, 100, 100, 100};

    float cam_speed = 5.0f;
    float zoom_speed = 0.02f;

    while(gfx.process_messages()) {
        
        Input::update();

        // keyboard
        if(Input::is_key_down('W')) camera.move(0, -cam_speed);
        if(Input::is_key_down('S')) camera.move(0, cam_speed);
        if(Input::is_key_down('A')) camera.move(-cam_speed, 0);
        if(Input::is_key_down('D')) camera.move(cam_speed, 0);
        
        if(Input::is_key_down('Q')) camera.set_zoom(camera.zoom() - zoom_speed);
        if(Input::is_key_down('E')) camera.set_zoom(camera.zoom() + zoom_speed);
        
        if(Input::is_key_down(VK_LEFT)) camera.set_rotation(camera.rotation_deg() - 1.0f);
        if(Input::is_key_down(VK_RIGHT)) camera.set_rotation(camera.rotation_deg() + 1.0f);

        
        
        gfx.begin_draw();
        gfx.clear(background_c);

        camera.apply(gfx.target(),screen);

        gfx.set_color(blue);
        for(int i = 0; i< 10; i++)
        {
            rect_t temp = block;
            temp.x *= i;
            gfx.fill_rect(temp);
            
        }
        brown_ball.draw(_brown_ball_coords);

        camera.reset(gfx.target());

        
        hud.set_color(black);
        hud.draw(L"Camera X: " + std::to_wstring((int)camera.x()), camera_x_rect);
        hud.draw(L"Camera Y: " + std::to_wstring((int)camera.y()), camera_y_rect);
        hud.draw(L"Zoom: " + std::to_wstring(camera.zoom()), zoom_rect);

        gfx.end_draw();
  
    }



    return 0;
}