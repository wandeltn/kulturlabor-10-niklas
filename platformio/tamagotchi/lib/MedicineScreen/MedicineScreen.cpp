#include <MedicineScreen.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <Bitmaps.hpp>
#include <MainScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

MedicineScreen::MedicineScreen(): BaseScreen(3) {
    Serial.println("inside MedicineScreen constructor");

    render_list.push_back(new SubScreenOptions{
        display_options, 
        (unsigned char)(sizeof(display_options) / sizeof(display_options[0]))
        }
    );
    render_list.push_back(new DisplayBitmap{&Bitmaps::medicine_menu_icon_image, 0, 48});
}

void MedicineScreen::onButtonBPressed() {
    switch (current_menu_position)
    {
    case 0:
        // Vaccination
        tamaStatus.health += 10;
        tamaStatus.happyness += -10;
        break;
    case 1:
        // Medicine
        tamaStatus.health += 10;
        tamaStatus.happyness += -5;
        break;
    case 2:
        // Doctor
        tamaStatus.health += 5;
        tamaStatus.happyness += 2;
        break;
    
    default:
        delete active_screen;
        active_screen = new MainScreen();
        break;
    }
    Serial.print("changed health value to: ");
    Serial.println(tamaStatus.health);
    Serial.print("changed happyness vlaue to: ");
    Serial.println(tamaStatus.happyness);
}