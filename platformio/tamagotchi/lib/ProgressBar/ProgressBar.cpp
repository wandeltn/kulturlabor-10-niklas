#include <ProgressBar.hpp>

ProgressBar::ProgressBar(unsigned short int x,
    unsigned short int y,
    unsigned short int w,
    unsigned short int h,
    short int fill_height)
{
    Serial.println("inside RAMProgressBar constructor");
    positionX = x;
    positionY = y;
    width = w;
    height = h;
    display_fill_height = fill_height;
}

void ProgressBar::render(Display& display, unsigned short int current_menu_position)
{
    display.drawRect(
        positionX,
        positionY,
        width,
        height,
        SSD1306_WHITE
    );
    display.fillRect(
        positionX,
        positionY,
        display_fill_height,
        height,
        SSD1306_WHITE
    );
}
