#include <MainScreen.hpp>
#include "../Renderables/MainMenuIcons/MainMenuIcons.hpp"
#include <IconsBar.hpp>
#include <Bitmaps.hpp>
#include <TamaStatus.hpp>
#include <FoodScreen.hpp>
#include <LightScreen.hpp>
#include <PlayScreen.hpp>
#include <MedicineScreen.hpp>
#include <PoopScreen.hpp>
#include <StatsScreen.hpp>
#include <DiciplineScreen.hpp>
#include <SettingsScreen.hpp>
#include <Tama.hpp>
#include <BatteryIndicator.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

MainScreen::MainScreen(): BaseScreen(7) {
    render_list.push_back(new MainMenuIcons());
    render_list.push_back(new IconsBar{&Bitmaps::poop_icon_image, &tamaStatus.poop_on_screen, 105});
    render_list.push_back(new IconsBar{&Bitmaps::stone_icon_image, &tamaStatus.weight, 17, true});
    render_list.push_back(new Tama{});
    render_list.push_back(new BatteryIndicator{97, 0});
}

void MainScreen::onButtonBPressed() {
    delete active_screen;
    switch (current_menu_position)
    {
    case 0:
        #ifdef DEBUG
        Serial.println("getting new FoodScreen");
        #endif
        active_screen = new FoodScreen{};
        break;
    case 1:
        #ifdef DEBUG
        Serial.println("getting new LightScreen");
        #endif
        active_screen = new LightScreen{};
        break;
    case 2:
        #ifdef DEBUG
        Serial.println("getting new PlayMenu");
        #endif
        active_screen = new PlayScreen{};
        break;
    case 3:
        #ifdef DEBUG
        Serial.println("getting new MedicineScreen");
        #endif
        active_screen = new MedicineScreen{};
        break;
    case 4:
        #ifdef DEBUG
        Serial.println("getting new PoopScreen");
        #endif
        active_screen = new PoopScreen{};
        break;
    case 5:
        #ifdef DEBUG
        Serial.println("getting new StatsScreen");
        #endif
        active_screen = new StatsScreen{};
        break;
    case 6:
        #ifdef DEBUG
        Serial.println("getting new DiciplineScreen");
        #endif
        active_screen = new DiciplineScreen{};
        break;
    case 7:
        #ifdef DEBUG
        Serial.println("getting new SettingsScreen");
        #endif
        active_screen = new SettingsScreen{};
        break;
    default:
        active_screen = new MainScreen{};
        break;
    }
}

