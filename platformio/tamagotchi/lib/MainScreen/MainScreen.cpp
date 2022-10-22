#include <MainScreen.hpp>
#include "../Renderables/MainMenuIcons/MainMenuIcons.hpp"
#include <FoodScreen.hpp>
#include <LightScreen.hpp>
#include <PlayScreen.hpp>
#include <MedicineScreen.hpp>
#include <PoopScreen.hpp>
#include <DiciplineScreen.hpp>

extern BaseScreen* active_screen;

MainScreen::MainScreen(): BaseScreen(7) {
    render_list.push_back(new MainMenuIcons());

}

void MainScreen::onButtonBPressed() {
    delete active_screen;
    switch (current_menu_position)
    {
    case 0:
        Serial.println("getting new FoodScreen");
        active_screen = new FoodScreen{};
        break;
    case 1:
        Serial.println("getting new LightScreen");
        active_screen = new LightScreen{};
        break;
    case 2:
        Serial.println("getting new PlayMenu");
        active_screen = new PlayScreen{};
        break;
    case 3:
        Serial.println("getting new MedicineScreen");
        active_screen = new MedicineScreen{};
        break;
    case 4:
        Serial.println("getting new PoopScreen");
        active_screen = new PoopScreen{};
        break;
    case 6:
        Serial.println("getting new DiciplineScreen");
        active_screen = new DiciplineScreen{};
        break;
    default:
        active_screen = new MainScreen{};
        break;
    }
}

