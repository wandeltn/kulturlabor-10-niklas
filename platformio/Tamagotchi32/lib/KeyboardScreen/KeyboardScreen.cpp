#include <KeyboardScreen.hpp>
#include <DrawKeyboard.hpp>

extern bool schedule_rerender;
extern BaseScreen* active_screen;

KeyboardScreen::KeyboardScreen(
    std::string output_string, 
    BaseScreen* return_screen
    ): BaseScreen(25)
{
    output_string_ = output_string;
    return_screen_ = return_screen;

    render_list.push_back(new DrawKeyboard{});    
}

void KeyboardScreen::onButtonBPressed()
{
    char alphabet[27] = {"abcdefghijklmnopqrstuvwxyz"};
    output_string_.push_back(alphabet[current_menu_position]);
}

void KeyboardScreen::onButtonDPressed()
{
    delete active_screen;
    active_screen = return_screen_;
}


