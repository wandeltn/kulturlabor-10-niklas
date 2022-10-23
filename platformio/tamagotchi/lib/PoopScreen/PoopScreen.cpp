#include <PoopScreen.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <Bitmaps.hpp>
#include <StatsDisplay.hpp>
#include <MainScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

PoopScreen::PoopScreen(): BaseScreen(1) {
    #ifdef DEBUG
    Serial.println("inside PoopScreen constructor");
    #endif

    render_list.push_back(new SubScreenOptions{display_options, (unsigned char)(sizeof(display_options) / sizeof(display_options[0]))});
    render_list.push_back(new DisplayBitmap{&Bitmaps::poop_menu_icon_image, 112, 0});
    render_list.push_back(new StatsDisplay{&tamaStatus.poop_on_screen, 120, 55});
}

void PoopScreen::onButtonBPressed() {
    switch (current_menu_position)
    {
    case 0:
        //Burger
        tamaStatus.clear_poop();
        #ifdef DEBUG
        Serial.println("cleared all poop");
        #endif
        break;

    default:
        delete active_screen;
        active_screen = new MainScreen();
        break;
    }
}