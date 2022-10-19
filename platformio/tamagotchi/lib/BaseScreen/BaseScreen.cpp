#include <BaseScreen.hpp>
#include <Renderable.hpp>

BaseScreen::BaseScreen() {
        Serial.println(F("Inside BaseScreen constructor"));
}
void BaseScreen::render(Display &display, unsigned short int current_menu_position)
{
	for (Renderable* element: render_list) {
                element->render(display, current_menu_position);               
        }
}