#include <DisplayText.hpp>

DisplayText::DisplayText(short int positionX, short int positionY, std::string text)
{
    position_X = positionX;
    position_Y = positionY;
    display_text = text;
}

void DisplayText::render(Display &display, unsigned short int current_menu_position)
{
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(position_X, position_Y);
    display.print(display_text.c_str());
}
