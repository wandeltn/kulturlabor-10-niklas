#include <ResetScreen.hpp>
#include "SubScreenOptions/SubScreenOptions.hpp"
#include <TamaStatus.hpp>
#include <MainScreen.hpp>

extern BaseScreen* active_screen;
extern TamaStatus tamaStatus;

ResetScreen::ResetScreen(): BaseScreen(2) 
{
    render_list.push_back(new SubScreenOptions{display_options, sizeof(display_options) / sizeof(display_options[0])});
}

void ResetScreen::onButtonBPressed()
{
    delete active_screen;
    switch (current_menu_position)
    {
    case 0:
        tamaStatus.reset();
        break;
    
    default:
        break;
    }
    active_screen = new MainScreen();
}
