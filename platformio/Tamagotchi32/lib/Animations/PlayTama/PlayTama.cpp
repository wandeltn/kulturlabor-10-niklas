#include <PlayTama/PlayTama.hpp>
#include <PlayScreen.hpp>
#include <Bitmaps.hpp>
#include <MainScreen.hpp>
#include <DisplayBitmap/DisplayBitmap.hpp>
#include <BaseScreen.hpp>
#include <UMS3.h>

#define ANIMATION_DELAY 500

extern UMS3 ums3;
extern BaseScreen* active_screen;
extern bool schedule_rerender;


PlayTama::PlayTama(short play_action, short frame_number): BaseScreen(1)
{
    playAction = play_action;
    frameNumber = frame_number;
    call_time = millis() + ANIMATION_DELAY;
}

void PlayTama::onButtonBPressed()
{
    delete active_screen;
    active_screen = new PlayScreen();
}

void PlayTama::updateScreen()
{
    if (call_time <= millis()) {
        for (Renderable* render_item : render_list) {
            delete render_item;
            render_item = nullptr;
        }
        render_list.clear();
        switch (playAction)
        {
        case 0:
            // soccer
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::soccer_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::soccer_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::soccer_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;

            default:
                delete active_screen;
                active_screen = new MainScreen();
                break;
            }
            break;
        
        case 1:
            // badminton
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::badminton_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::badminton_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::badminton_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;

            default:
                delete active_screen;
                active_screen = new MainScreen();
                break;
            }
            break;

        case 2:
            // hockey
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::hockey_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::hockey_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::hockey_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;

            default:
                delete active_screen;
                active_screen = new MainScreen();
                break;
            }
            break;

        case 3:
            // chess
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::chess_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::chess_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::PlayScreen::chess_field_image,
                    0,
                    0
                });
                call_time = millis() + ANIMATION_DELAY;
                break;

            default:
                delete active_screen;
                active_screen = new MainScreen();
                break;
            }
            break;

        default:
            break;
        }
        schedule_rerender = true;
    }
}

short PlayTama::frameNumber = 0;
short PlayTama::playAction = 0;