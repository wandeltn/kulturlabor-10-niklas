#include <DiagnosticsScreen.hpp>
#include <SettingsScreen.hpp>
#include <BTManager.hpp>
#include <DisplayText.hpp>
#include <MainScreen.hpp>

extern BTManager btManager;
extern BaseScreen* active_screen;

DiagnosticsScreen::DiagnosticsScreen(): BaseScreen(0)
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
    active_screen = new MainScreen();
}

void DiagnosticsScreen::onButtonDPressed()
{
    delete active_screen;
    active_screen = new SettingsScreen();
}

void DiagnosticsScreen::updateScreen()
{
    for (Renderable* pointer : render_list) {
        delete pointer;
        pointer = nullptr;
    }
    render_list.clear();

    render_list.push_back(new DisplayText{
        25, 
        8,
        std::to_string(btManager.getNearbyDevices())
    });
}
