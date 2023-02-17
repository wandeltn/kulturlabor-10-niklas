#include <ThanksScreen.hpp>
#include <DisplayText.hpp>
#include <MainScreen.hpp>


extern BaseScreen* active_screen;

ThanksScreen::ThanksScreen(): BaseScreen(0)
{
    render_list.push_back(new DisplayText{25, 0, display_text});
}

void ThanksScreen::onButtonBPressed()
{
    delete active_screen;
    active_screen = new MainScreen();
}
