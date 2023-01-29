#include <HealTama/HealTama.hpp>
#include <Bitmaps.hpp>
#include <DisplayBitmap/DisplayBitmap.hpp>
#include <MainScreen.hpp>
#include <MedicineScreen.hpp>
#include <TamaStatus.hpp>
#include <UMS3.h>

#define ANIMATION_DELAY 500
#define ANIMATION_0_X   60
#define ANIMATION_0_Y   48

#define ANIMATION_1_X   50
#define ANIMATION_1_Y   36

#define ANIMATION_2_X   40
#define ANIMATION_2_Y   25

extern UMS3 ums3;
extern TamaStatus tamaStatus;
extern BaseScreen* active_screen;
extern bool schedule_rerender;

HealTama::HealTama(unsigned short menu_position, unsigned short frame_num): BaseScreen(1)
{
    menuPosition = menu_position;
    frameNumber = frame_num;
    call_time = millis() + ANIMATION_DELAY;
}

void HealTama::onButtonBPressed()
{
    delete active_screen;
    active_screen = new MedicineScreen();
}

void HealTama::updateScreen()
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
        switch (menuPosition)
        {
        case 0:
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::MedicineScreen::syringe_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                });
                break;
            
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::MedicineScreen::syringe_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                });
                break;
            
            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::MedicineScreen::syringe_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
                });
                break;

            default:
                delete active_screen;
                active_screen = new MedicineScreen();
                break;
            }
        break;
        
        case 1:
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::MedicineScreen::medicine_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                });
                break;

            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::MedicineScreen::medicine_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                });
                break;
            
            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::MedicineScreen::medicine_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
                });            
                break;
            
            default:
                delete active_screen;
                active_screen = new MedicineScreen();
                break;
            }

        case 2:
            switch (frameNumber)
            {
            case 0:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::MedicineScreen::bandAid_image,
                    ANIMATION_0_X,
                    ANIMATION_0_Y
                });
                break;
            
            case 1:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::MedicineScreen::bandAid_image,
                    ANIMATION_1_X,
                    ANIMATION_1_Y
                });
                break;
            
            case 2:
                render_list.push_back(new DisplayBitmap{
                    &Bitmaps::Animations::MedicineScreen::bandAid_image,
                    ANIMATION_2_X,
                    ANIMATION_2_Y
                });
                break;

            default:
                delete active_screen;
                active_screen = new MedicineScreen();
                break;
            }

        default:
            break;
        }
        call_time = millis() + ANIMATION_DELAY;
        frameNumber++;
        schedule_rerender = true;
    }
}


short HealTama::frameNumber = 0;
short HealTama::menuPosition = 0;
unsigned long HealTama::call_time = 0;