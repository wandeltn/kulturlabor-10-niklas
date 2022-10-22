#include <MainScreen.hpp>
#include "../Renderables/MainMenuIcons/MainMenuIcons.hpp"
#include <FoodScreen.hpp>

extern BaseScreen* active_screen;

MainScreen::MainScreen() {
    render_list.push_back(new MainMenuIcons());
}

void MainScreen::onButtonBPressed(unsigned short int current_menu_position) {
    if (current_menu_position == 0) {
        delete active_screen;
        active_screen = new FoodScreen{};
    }
}