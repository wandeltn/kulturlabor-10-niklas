#include <PoopScreen.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <Bitmaps.hpp>
#include <MainScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

PoopScreen::PoopScreen(): BaseScreen(1) {
    Serial.println("inside PoopScreen constructor");

    render_list.push_back(new SubScreenOptions{display_options, (unsigned char)(sizeof(display_options) / sizeof(display_options[0]))});
    render_list.push_back(new DisplayBitmap{&Bitmaps::food_menu_icon_image, 0, 0});
}

void PoopScreen::onButtonBPressed() {
    switch (current_menu_position)
    {
    case 0:
        //Burger
        tamaStatus.clear_poop();
        Serial.println("cleared all poop");
        break;

    default:
        delete active_screen;
        active_screen = new MainScreen();
        break;
    }
}