#include <DiciplineScreen.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <Bitmaps.hpp>
#include <MainScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

DiciplineScreen::DiciplineScreen(): BaseScreen(4) {
    #ifdef DEBUG
    Serial.println("inside DiciplineScreen constructor");
    #endif

    render_list.push_back(new SubScreenOptions{display_options, (unsigned char)(sizeof(display_options) / sizeof(display_options[0]))});
    render_list.push_back(new DisplayBitmap{&Bitmaps::dicipline_menu_icon_image, 112, 32});
}

void DiciplineScreen::onButtonBPressed() {
    switch (current_menu_position)
    {
    case 0:
        // Time together
        tamaStatus.health += 10;
        tamaStatus.dicipline += 2;
        break;
    case 1:
        // set expectations
        tamaStatus.health += -5;
        tamaStatus.dicipline += 2;
        break;
    case 2:
        // use concequences
        tamaStatus.health += -10;
        tamaStatus.dicipline += 3;
        break;
    case 3:
        // do an activity
        tamaStatus.health += 10;
        tamaStatus.dicipline += 3;
        break;
    default:
        delete active_screen;
        active_screen = new MainScreen();
        break;
    }
    #ifdef DEBUG
    Serial.print("changed dicipline value to: ");
    Serial.println(tamaStatus.dicipline);
    Serial.print("changed health value to: ");
    Serial.println(tamaStatus.health);
    #endif
}

const char* DiciplineScreen::display_options[5] = {
    "  Time together",
    "  Set expectations",
    "  Use concequences",
    "  Do an activity",
    "  Exit"
};