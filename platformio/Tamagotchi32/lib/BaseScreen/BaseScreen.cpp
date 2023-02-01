#include <BaseScreen.hpp>
#include <Renderable.hpp>
#include <MainScreen.hpp>

extern BaseScreen* active_screen;
extern bool schedule_rerender;

BaseScreen::BaseScreen(unsigned char max_menu_position): 
    current_menu_position{0}, 
    max_menu_position_{max_menu_position} 
{
    #ifdef DEBUG
    Serial.println(F("Inside BaseScreen constructor"));
    #endif
}

BaseScreen::~BaseScreen() {
    for ( Renderable* render_item : render_list) {
        delete render_item;
        render_item = nullptr;
    }
    render_list.clear();
}

void BaseScreen::render(Display &display)
{
	for (Renderable* element: render_list) {
        element->render(display, current_menu_position);               
    }
}

void BaseScreen::updateScreen()
{
    for (Renderable* element: render_list) {
        element->update();
    }
}

void BaseScreen::onButtonAPressed()
{
    if (++current_menu_position > max_menu_position_) {
        current_menu_position = 0;
    }
}

void BaseScreen::onButtonCPressed()
{
    if (current_menu_position == 0) {
        current_menu_position = max_menu_position_;
    } else {
        current_menu_position--;
    }
}

void BaseScreen::onButtonDPressed()
{
    delete active_screen;
    active_screen = new MainScreen();
}