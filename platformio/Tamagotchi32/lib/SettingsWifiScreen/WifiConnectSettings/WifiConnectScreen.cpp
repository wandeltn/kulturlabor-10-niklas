#include <WifiConnectSettings/WifiConnectScreen.hpp>
#include <BaseScreen.hpp>
#include <MainScreen.hpp>
#include <WifiSettingsScreen.hpp>

extern BaseScreen* active_screen;

WifiConnectScreen::WifiConnectScreen(): BaseScreen(0)
{
    
}

void WifiConnectScreen::onButtonBPressed()
{
    delete active_screen;
    active_screen = new MainScreen();   
}

void WifiConnectScreen::onButtonDPressed()
{
    delete active_screen;
    active_screen = new WifiSettingsScreen();
}
