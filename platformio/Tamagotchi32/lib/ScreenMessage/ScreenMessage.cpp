#include <ScreenMessage.hpp>
#include <DisplayText.hpp>

extern BaseScreen* active_screen;

ScreenMessage::ScreenMessage(std::string* display_text, BaseScreen* return_screen): BaseScreen(0)
{
    return_screen_ = return_screen;
    render_list.push_back(new DisplayText{
        50,
        50,
        display_text
    });
}

ScreenMessage::ScreenMessage(std::string display_text, BaseScreen* return_screen): BaseScreen(0)
{
    return_screen_ = return_screen;
    render_list.push_back(new DisplayText{
        50,
        50,
        display_text
    });
}

void ScreenMessage::onButtonBPressed()
{
    delete active_screen;
    active_screen = return_screen_;
}

void ScreenMessage::onButtonDPressed()
{
    delete active_screen;
    active_screen = return_screen_;
}
