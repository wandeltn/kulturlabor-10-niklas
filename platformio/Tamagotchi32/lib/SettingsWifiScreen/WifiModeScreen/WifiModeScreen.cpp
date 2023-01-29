#include <WifiModeScreen/WifiModeScreen.hpp>
#include <BaseScreen.hpp>
#include <MainScreen.hpp>
#include <SubScreenOptions/SubScreenOptions.hpp>
#include <WifiManager.hpp>
#include <SettingsScreen.hpp>

extern BaseScreen* active_screen;
extern WifiManager wifiManager;

WifiModeScreen::WifiModeScreen(): BaseScreen(1)
{
    render_list.push_back(new SubScreenOptions{display_options, sizeof(display_options) / sizeof(display_options[0])});
}

void WifiModeScreen::onButtonBPressed()
{
    delete active_screen;
    switch (current_menu_position)
    {
    case 0:
        wifiManager.switchMode(WIFI_AP);
        active_screen = new MainScreen();
        break;
    
    case 1:
        wifiManager.switchMode(WIFI_STA);
        active_screen = new MainScreen();
        break;

    default:
        active_screen = new MainScreen();
        break;
    }
}

void WifiModeScreen::onButtonDPressed()
{
    delete active_screen;
    active_screen = new SettingsScreen();
}

