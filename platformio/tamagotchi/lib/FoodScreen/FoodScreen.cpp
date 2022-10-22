#include <FoodScreen.hpp>
#include "FoodScreenOptions/FoodScreenOptions.hpp"
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <Bitmaps.hpp>
#include <MainScreen.hpp>

extern BaseScreen* active_screen;

FoodScreen::FoodScreen() {
    render_list.push_back(new FoodScreenOptions{});

    render_list.push_back(new DisplayBitmap{&Bitmaps::food_menu_icon_image, 0, 0});
}

void FoodScreen::onButtonBPressed(unsigned short int current_menu_position) {
    delete active_screen;
    active_screen = new MainScreen;
}