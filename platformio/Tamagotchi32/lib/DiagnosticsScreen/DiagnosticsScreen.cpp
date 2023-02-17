#include <DiagnosticsScreen.hpp>
#include <SettingsScreen.hpp>
#include <BTManager.hpp>
#include <DisplayText.hpp>
#include <MainScreen.hpp>
#include <ThanksScreen.hpp>

extern BTManager btManager;
extern BaseScreen* active_screen;

DiagnosticsScreen::DiagnosticsScreen(): BaseScreen(2)
{
    render_list.push_back(new DisplayText{
        25, 
        8,
        std::to_string(btManager.getNearbyDevices())
    });
}

void DiagnosticsScreen::onButtonBPressed()
{
    delete active_screen;
    if (current_menu_position != 1) {
        active_screen = new MainScreen();
    } else {
        active_screen = new ThanksScreen();    
    }
}

void DiagnosticsScreen::onButtonDPressed()
{
    delete active_screen;
    active_screen = new SettingsScreen();
}
