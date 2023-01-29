#include <FoodScreen.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <StatsDisplay.hpp>
#include <Bitmaps.hpp>
#include <MainScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>
#include <FeedTama/FeedTama.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

FoodScreen::FoodScreen(): BaseScreen(6) {
    #ifdef DEBUG
    Serial.println("inside FoodScreen constructor");
    #endif

    render_list.push_back(new SubScreenOptions{display_options, (unsigned char)(sizeof(display_options) / sizeof(display_options[0]))});
    render_list.push_back(new DisplayBitmap{&Bitmaps::food_menu_icon_image, 0, 0});
    render_list.push_back(new StatsDisplay{&tamaStatus.hunger, 0, 56});
}

void FoodScreen::onButtonBPressed() {
    delete active_screen;
    switch (current_menu_position)
    {
    case 0:
        //Burger
        tamaStatus.hunger += 520;
        tamaStatus.happyness += 2;
        tamaStatus.add_diet_counter(-2);
        active_screen = new FeedTama(0, 0);
        break;
    case 1:
        // Pasta
        tamaStatus.hunger += 280;
        tamaStatus.happyness += 2;
        tamaStatus.add_diet_counter(-1);
        active_screen = new FeedTama(1, 0);
        break;
    case 2:
        // Muffin
        tamaStatus.hunger += 440;
        tamaStatus.happyness += 3;
        tamaStatus.add_diet_counter(-2);
        active_screen = new FeedTama(2, 0);
        break;
    case 3:
        // Broccoli
        tamaStatus.hunger += 30;
        tamaStatus.happyness += -3;
        tamaStatus.add_diet_counter(2);
        active_screen = new FeedTama(3, 0);
        break;
    case 4:
        // Salad
        tamaStatus.hunger += 235;
        tamaStatus.happyness += -2;
        tamaStatus.add_diet_counter(3);
        active_screen = new FeedTama(4, 0);
        break;
    case 5:
        // Sushi
        tamaStatus.hunger += 150;
        tamaStatus.happyness += 0;
        tamaStatus.add_diet_counter(0);
        active_screen = new FeedTama(5, 0);
    case 6:
        // Crepes
        tamaStatus.hunger += 180;
        tamaStatus.happyness += 4;
        tamaStatus.add_diet_counter(2);
        active_screen = new FeedTama(6, 0);
        break;
    
    default:
        active_screen = new MainScreen();
        break;
    }
    #ifdef DEBUG
    Serial.print("changed hunger value to: ");
    Serial.println(tamaStatus.hunger);
    Serial.print("changed happyness vlaue to: ");
    Serial.println(tamaStatus.happyness);
    Serial.print("changed health value to: ");
    Serial.println(tamaStatus.health);
    #endif
}