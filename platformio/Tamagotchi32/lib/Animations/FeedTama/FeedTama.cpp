#include <FeedTama/FeedTama.hpp>
#include <Bitmaps.hpp>
#include <DisplayBitmap/DisplayBitmap.hpp>
#include <TamaStatus.hpp>
#include <MainScreen.hpp>
#include <BaseScreen.hpp>
#include <FoodScreen.hpp>
#include <UMS3.h>

#define ANIMATION_DELAY 500
#define ANIMATION_0_X   60
#define ANIMATION_0_Y   48
#define ANIMATION_1_X   50
#define ANIMATION_1_Y   50
#define ANIMATION_2_X   40
#define ANIMATION_2_Y   25

extern UMS3 ums3;
extern TamaStatus tamaStatus;
extern BaseScreen* active_screen;
extern bool schedule_rerender;

FeedTama::FeedTama(unsigned short food_item, unsigned short frame_num): BaseScreen(1)
{
    foodItem = food_item;
    frameNumber = frame_num;

    call_time = millis() + ANIMATION_DELAY;
}

void FeedTama::onButtonBPressed()
{
    delete active_screen;
    active_screen = new FoodScreen();
}

void FeedTama::updateScreen()
{
    if (call_time <= millis()) {
        for (Renderable* pointer : render_list) {
            delete pointer;
            pointer = nullptr;
        }
        render_list.clear();
        render_list.push_back(new DisplayBitmap{
            &tamaStatus.current_display_state,
            16,
            16
        });
        switch (foodItem)
        {
        case 0:
            // Burger
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::burger_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::burger_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;

            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::burger_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
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
            // Pasta
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::pasta_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::pasta_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;

            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::pasta_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
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
            // Muffin
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::muffin_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::muffin_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;

            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::muffin_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
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
            // Broccoli
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::broccoli_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::broccoli_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;

            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::broccoli_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;           
            
            default:
                delete active_screen;
                active_screen = new MainScreen();
                break;
            }
            break;

        case 4:
            // Salad
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::salad_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::salad_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;

            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::salad_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;           
            
            default:
                delete active_screen;
                active_screen = new MainScreen();
                break;
            }
            break;

        case 5:
            // Sushi
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::sushi_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::sushi_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;

            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::sushi_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;           
            
            default:
                delete active_screen;
                active_screen = new MainScreen();
                break;
            }
            break;

        case 6:
            // Crepes
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::crepes_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;
            
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::crepes_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                    });
                call_time = millis() + ANIMATION_DELAY;
                break;

            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::FoodScreen::crepes_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
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
            delete active_screen;
            active_screen = new MainScreen();
            break;
        }
        frameNumber++;
        schedule_rerender = true;
    }
}

short FeedTama::frameNumber = 0;
short FeedTama::foodItem = 0;