#include <StatsScreen.hpp>
#include <ProgressBar.hpp>
#include <MainScreen.hpp>
#include <TamaStatus.hpp>
#include <DisplayText.hpp>
#include <Bitmaps.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <string>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

StatsScreen::StatsScreen(): BaseScreen(1)
{
    #ifdef DEBUG
    Serial.println("inside StatsScreen constructor");
    #endif
    render_list.push_back(new DisplayBitmap{&Bitmaps::food_menu_icon_image, 110, 48});

    render_list.push_back(new ProgressBar{8, 8, 100, 6, tamaStatus.happyness});
    render_list.push_back(new ProgressBar{8, 22, 100, 6, tamaStatus.health});
    render_list.push_back(new ProgressBar{8, 36, 100, 6, tamaStatus.dicipline});
    render_list.push_back(new ProgressBar{8, 50, 100, 6, tamaStatus.weight});
    std::string bar_list[4] = {
        "Happyness",
        "Health",
        "Dicipline",
        "Weight"
    };
    for (int index = 0; index < (sizeof(bar_list) / sizeof(bar_list[0])); index++) {
        render_list.push_back(new DisplayText{15, index * 14, bar_list[index]});
    }
}

void StatsScreen::onButtonBPressed()
{
    #ifdef DEBUG
    Serial.println("exiting settingsScreen");
    #endif
    delete active_screen;
    active_screen = new MainScreen();
}
