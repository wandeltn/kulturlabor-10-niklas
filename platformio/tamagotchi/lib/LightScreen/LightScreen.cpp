#include <LightScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <Bitmaps.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <TamaStatus.hpp>
#include <MainScreen.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

LightScreen::LightScreen(): BaseScreen(2)
{
    Serial.println("inside LightScreen constructor");

    render_list.push_back(new SubScreenOptions{
        display_options,
        (unsigned char)(sizeof(display_options) / sizeof(display_options[0]))
    });
    render_list.push_back(new DisplayBitmap{&Bitmaps::light_menu_icon_image, 0, 0});
}

void LightScreen::onButtonBPressed()
{
    switch (current_menu_position)
    {
    case 0:
        tamaStatus.toggle_light(true);
        Serial.println("turned on light");
        break;
    case 1:
        tamaStatus.toggle_light(false);
        Serial.println("turned off light");    
    default:
        delete active_screen;
        active_screen = new MainScreen();
        break;
    }
}

