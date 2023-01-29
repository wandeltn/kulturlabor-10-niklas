#include <CleanPoop/CleanPoop.hpp>
#include <Bitmaps.hpp>
#include <Display.hpp>
#include <DisplayBitmap/DisplayBitmap.hpp>
#include <DisplayFastLine/DisplayFastLine.hpp>
#include <MainScreen.hpp>
#include <PoopScreen.hpp>
#include <TamaStatus.hpp>
#include <UMS3.h>

#define ANIMATION_DELAY 50

extern UMS3 ums3;
extern TamaStatus tamaStatus;
extern BaseScreen* active_screen;
extern bool schedule_rerender;


CleanPoop::CleanPoop(unsigned short menu_item, unsigned short frame_num): BaseScreen(1)
{
    menuItem = menu_item;
    frameNumber = frame_num;
    call_time = millis() + ANIMATION_DELAY;
}

void CleanPoop::onButtonBPressed()
{
    delete active_screen;
    active_screen = new PoopScreen();
}

void CleanPoop::updateScreen()
{
    if (call_time <= millis()) {
        for (Renderable* pointer : render_list) {
            delete pointer;
            pointer = nullptr;
        }
        render_list.clear();

        if (frameNumber <= 128) {
            render_list.push_back(new DisplayFastLine{frameNumber});
            render_list.push_back(new DisplayFastLine{(unsigned short)(frameNumber -2)});
            render_list.push_back(new DisplayFastLine{(unsigned short)(frameNumber -4)});
            frameNumber++;
        } else {
            delete active_screen;
            active_screen = new PoopScreen();
        }
        schedule_rerender = true;
    }
}

unsigned short int CleanPoop::frameNumber = 0;
short int CleanPoop::menuItem = 0;
