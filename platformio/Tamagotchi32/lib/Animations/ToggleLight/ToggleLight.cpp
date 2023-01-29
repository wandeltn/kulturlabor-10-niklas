#include <ToggleLight/ToggleLight.hpp>
#include <Bitmaps.hpp>
#include <DisplayBitmap/DisplayBitmap.hpp>
#include <BaseScreen.hpp>
#include <MainScreen.hpp>
#include <LightScreen.hpp>
#include <Timer.hpp>
#include <Timeable.hpp>
#include <UMS3.h>

extern UMS3 ums3;
extern BaseScreen* active_screen;
extern Timer timer;
extern bool schedule_rerender;

ToggleLight::ToggleLight(bool light_on, unsigned short frame_num): BaseScreen(1)
{
    lightOn = light_on;
    frameNumber = frame_num;

    call_time = millis() + 500;
}


void ToggleLight::onButtonBPressed()
{
    delete active_screen;
    active_screen = new LightScreen();
}

void ToggleLight::updateScreen()
{
    if (call_time <= millis()) {
        for (Renderable* pointer : render_list) {
            delete pointer;
            pointer = nullptr;
        }
        render_list.clear();
        switch (frameNumber++)
        {
            case 0:
                call_time = millis() + 500;
                if (lightOn) {
                    render_list.push_back(new DisplayBitmap(&Bitmaps::Animations::LightScreen::lamp_off_image, 32, 0));
                    ums3.setPixelColor(0xFF0000);
                } else {
                    render_list.push_back(new DisplayBitmap(&Bitmaps::Animations::LightScreen::lamp_on_image, 32, 0));
                    ums3.setPixelColor(0x0000FF);
                }
                // active_screen = new ToggleLight(lightOn, frame_num++);
                break;

            case 1:
                call_time = millis() + 500;
                render_list.push_back(new DisplayBitmap(&Bitmaps::Animations::LightScreen::lamp_half_on_image, 32, 0));
                ums3.setPixelColor(0x00FF00);
                // active_screen = new ToggleLight(lightOn, frame_num++);
                break;

            case 2:
                call_time = millis() + 500;
                if (lightOn) {
                    render_list.push_back(new DisplayBitmap(&Bitmaps::Animations::LightScreen::lamp_on_image, 32, 0));
                    ums3.setPixelColor(0x0000FF);
                } else {
                    render_list.push_back(new DisplayBitmap(&Bitmaps::Animations::LightScreen::lamp_off_image, 32, 0));
                }
                // active_screen = new ToggleLight(lightOn, frame_num++);
                break;
            default:
                delete active_screen;
                active_screen = new MainScreen();
        }
        schedule_rerender = true;
    }
}

int16_t ToggleLight::frameNumber = 0;
bool ToggleLight::lightOn = false;