#include <WifiConnectSettings/WifiConnectScreen.hpp>
#include <BaseScreen.hpp>
#include <MainScreen.hpp>

extern BaseScreen* active_screen;

WifiConnectScreen::WifiConnectScreen(): BaseScreen(1)
{
    
}

void WifiConnectScreen::onButtonBPressed()
{
    delete active_screen;

    active_screen = new MainScreen();   
}
