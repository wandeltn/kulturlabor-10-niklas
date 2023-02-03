#include <DrawLine.hpp>

DrawLine::DrawLine(
            uint8_t positionX1,
            uint8_t positionY1,
            uint8_t positionX2,
            uint8_t positionY2
            ): Renderable()
{
    positionX1_ = positionX1;
    positionY1_ = positionY1;
    positionX2_ = positionX2;
    positionY2_ = positionY2;
}

void DrawLine::render(Display &display, unsigned short current_menu_position)
{
    display.drawLine(
        positionX1_,
        positionY1_,
        positionX2_,
        positionY2_,
        SSD1306_WHITE
    );
}

