#include <WifiConnectSettings/WifiConnectScreen.hpp>
#include <BaseScreen.hpp>
#include <MainScreen.hpp>
#include <WifiSettingsScreen.hpp>
#include <DisplayText.hpp>
#include <WifiManager.hpp>

extern BaseScreen* active_screen;
extern WifiManager wifiManager;

WifiConnectScreen::WifiConnectScreen(): BaseScreen(0)
{
    render_list.push_back(new DisplayText{50, 50, "Press B to confirm"});
}

void WifiConnectScreen::updateScreen()
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
