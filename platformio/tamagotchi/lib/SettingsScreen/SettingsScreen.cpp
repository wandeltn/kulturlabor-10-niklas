#include <SettingsScreen.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <MainScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>
#include <RAMProgressBar.hpp>

extern BaseScreen* active_screen;

SettingsScreen::SettingsScreen(): BaseScreen(1) {
    Serial.println("inside SettingsScreen constructor");

    render_list.push_back(new RAMProgressBar{1, 1, 100, 6});
}

void SettingsScreen::onButtonBPressed()
{
    Serial.println("exiting settingsScreen");
    delete active_screen;
    active_screen = new MainScreen();
}