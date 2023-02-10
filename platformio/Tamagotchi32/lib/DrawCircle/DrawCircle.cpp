#include <DrawCircle.hpp>

DrawCircle::DrawCircle(uint8_t positionX, uint8_t positionY, uint8_t radius)
{
    positionX_ = positionX;
    positionY_ = positionY;
    radius_ = radius;
}

DrawCircle::DrawCircle(Vector2 position, uint8_t radius)
{
    positionX_ = position.x;
    positionY_ = position.y;
    radius_ = radius;
}

void DrawCircle::render(Display &display, unsigned short current_menu_position)
{
    display.drawCircle(
        positionX_,
        positionY_,
        radius_,
        SSD1306_WHITE
    );
}
