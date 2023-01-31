#include <SettingsScreen.hpp>
#include <MainScreen.hpp>
#include <ResetScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <DiagnosticsScreen.hpp>
#include <WifiSettingsScreen.hpp>
#include <RAMProgressBar.hpp>
#include <DisplayText.hpp>
#include <Timer.hpp>
#include <string>

extern BaseScreen* active_screen;
extern Timer timer;

SettingsScreen::SettingsScreen(): BaseScreen(3) {
    #ifdef DEBUG
    Serial.println("inside SettingsScreen constructor");
    #endif
    render_list.push_back(new SubScreenOptions{display_options, (unsigned char)(sizeof(display_options) / sizeof(display_options[0]))});
    render_list.push_back(new DisplayText{30, 30, std::to_string((int)timer.get_timer_amount())});
}

void SettingsScreen::onButtonBPressed()
{
    #ifdef DEBUG
    Serial.println("exiting settingsScreen");
    #endif
    delete active_screen;
    switch (current_menu_position)
    {
    case 0:
        active_screen = new WifiSettingsScreen();
        break;
    
    case 1:
        active_screen = new DiagnosticsScreen();
        break;

    case 2:
        active_screen = new ResetScreen();
        break;

    default:
        active_screen = new MainScreen();
        break;
    }
}