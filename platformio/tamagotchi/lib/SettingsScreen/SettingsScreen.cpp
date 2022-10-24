#include <SettingsScreen.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <MainScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>
#include <RAMProgressBar.hpp>
#include <DisplayText.hpp>
#include <Timer.hpp>
#include <string>

extern BaseScreen* active_screen;
extern Timer timer;

SettingsScreen::SettingsScreen(): BaseScreen(1) {
    Serial.println("inside SettingsScreen constructor");

    render_list.push_back(new RAMProgressBar{1, 1, 100, 6});
    render_list.push_back(new DisplayText{30, 30, std::to_string((int)timer.get_timer_amount())});
}

void SettingsScreen::onButtonBPressed()
{
    Serial.println("exiting settingsScreen");
    delete active_screen;
    active_screen = new MainScreen();
}