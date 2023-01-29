#include <ResetScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>
#include <MainScreen.hpp>
#include <SettingsScreen.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

ResetScreen::ResetScreen(): BaseScreen(1) 
{
    render_list.push_back(new SubScreenOptions{display_options, sizeof(display_options) / sizeof(display_options[0])});
}

void ResetScreen::onButtonBPressed()
{
    switch (current_menu_position)
    {
    case 0:
        tamaStatus.reset();
        break;
    
    default:
        break;
    }
    delete active_screen;
    active_screen = new MainScreen();
}

void ResetScreen::onButtonDPressed() 
{
    delete active_screen;
    active_screen = new SettingsScreen();
}