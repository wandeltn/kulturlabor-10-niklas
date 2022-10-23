#include <PlayScreen.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <Bitmaps.hpp>
#include <MainScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

PlayScreen::PlayScreen(): BaseScreen(5) {
    Serial.println("inside PlayScreen constructor");

    render_list.push_back(new SubScreenOptions{display_options, (unsigned char)(sizeof(display_options) / sizeof(display_options[0]))});
    render_list.push_back(new DisplayBitmap{&Bitmaps::play_menu_icon_image, 0, 32});
}

void PlayScreen::onButtonBPressed() {
    switch (current_menu_position)
    {
    case 0:
        //Soccer
        tamaStatus.hunger += 300;
        tamaStatus.happyness += 5;
        tamaStatus.health += 5;
        break;
    case 1:
        // Badminton
        tamaStatus.hunger += 300;
        tamaStatus.happyness += 5;
        tamaStatus.health += 5;
        break;
    case 2:
        // Hockey
        tamaStatus.hunger += 300;
        tamaStatus.happyness += 5;
        tamaStatus.health += 5;
        break;
    case 3:
        // Chess
        tamaStatus.hunger += 30;
        tamaStatus.happyness += 0;
        tamaStatus.health += 5;
        break;
    case 4:
        // Cards
        tamaStatus.hunger += 30;
        tamaStatus.happyness += 0;
        tamaStatus.health += 5;
        break;
    
    default:
        delete active_screen;
        active_screen = new MainScreen();
        break;
    }
    Serial.print("changed hunger value to: ");
    Serial.println(tamaStatus.hunger);
    Serial.print("changed happyness vlaue to: ");
    Serial.println(tamaStatus.happyness);
    Serial.print("changed health value to: ");
    Serial.println(tamaStatus.health);
}