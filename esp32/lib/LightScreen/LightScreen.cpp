#include <LightScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <Bitmaps.hpp>
#include <StatsDisplay.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <TamaStatus.hpp>
#include <MainScreen.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

LightScreen::LightScreen(): BaseScreen(2)
{
    #ifdef DEBUG
    Serial.println("inside LightScreen constructor");
    #endif

    render_list.push_back(new SubScreenOptions{
        display_options,
        (unsigned char)(sizeof(display_options) / sizeof(display_options[0]))
    });
    render_list.push_back(new DisplayBitmap{&Bitmaps::light_menu_icon_image, 0, 16});
    render_list.push_back(new StatsDisplay{&tamaStatus.light_on, 0, 56});

}

void LightScreen::onButtonBPressed()
{
    switch (current_menu_position)
    {
    case 0:
        tamaStatus.toggle_light(true);
        #ifdef DEBUG
        Serial.println("turned on light");
        #endif
        break;
    case 1:
        tamaStatus.toggle_light(false);
        #ifdef DEBUG
        Serial.println("turned off light"); 
        #endif
        break;
    default:
        delete active_screen;
        active_screen = new MainScreen();
        break;
    }
}

