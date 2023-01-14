#include <SettingsWifiScreen.hpp>
#include <SubScreenOptions/SubScreenOptions.hpp>
#include <MainScreen.hpp>
#include <BaseScreen.hpp>

extern BaseScreen* active_screen;

SettingsWifiScreen::SettingsWifiScreen(): BaseScreen(5)
{
    render_list.push_back(new SubScreenOptions{display_options, sizeof(display_options) / sizeof(display_options[0])});
}

void SettingsWifiScreen::onButtonBPressed()
{
    delete active_screen;
    switch (current_menu_position)
    {
    case 0:
        
        break;
    
    default:
        break;
    }
}
