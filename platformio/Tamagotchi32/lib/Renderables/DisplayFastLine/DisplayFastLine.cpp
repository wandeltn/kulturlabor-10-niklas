#include <DisplayFastLine/DisplayFastLine.hpp>


DisplayFastLine::DisplayFastLine(unsigned short int positionX)
{
    position_X = positionX;
}

void DisplayFastLine::render(Display &display, unsigned short int current_menu_position)
{
    display.drawFastVLine(position_X, 0, 64, SSD1306_WHITE);
}


