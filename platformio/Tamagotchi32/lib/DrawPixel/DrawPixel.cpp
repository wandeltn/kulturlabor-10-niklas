#include <DrawPixel.hpp>

DrawPixel::DrawPixel(short position_x, short position_y)
{
    positionX = position_x;
    positionY = position_y;
}

void DrawPixel::render(Display &display, unsigned short current_menu_position)
{
    display.drawPixel(
        positionX,
        positionY,
        SSD1306_WHITE
    );
}

