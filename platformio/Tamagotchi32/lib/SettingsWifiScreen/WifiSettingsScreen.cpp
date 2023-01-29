#include <WifiSettingsScreen.hpp>
#include <SubScreenOptions/SubScreenOptions.hpp>
#include <MainScreen.hpp>
#include <BaseScreen.hpp>
#include <WifiConnectSettings/WifiConnectScreen.hpp>
#include <WifiModeScreen/WifiModeScreen.hpp>

extern BaseScreen* active_screen;

WifiSettingsScreen::WifiSettingsScreen(): BaseScreen(5)
{
    render_list.push_back(new SubScreenOptions{display_options, sizeof(display_options) / sizeof(display_options[0])});
}

void WifiSettingsScreen::onButtonBPressed()
{
    delete active_screen;
    switch (current_menu_position)
    {
    case 0:
        active_screen = new WifiConnectScreen();
        break;
    
    case 1:
        active_screen = new WifiModeScreen();
        break;

    default:
        active_screen = new MainScreen();
        break;
    }
}
