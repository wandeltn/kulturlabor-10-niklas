#include "DisplayBitmap/DisplayBitmap.hpp"
#include <Bitmaps.hpp>

DisplayBitmap::DisplayBitmap(const ImageFormat* image, unsigned short int positionX, unsigned short int positionY)
{
    #ifdef DEBUG
    Serial.println("inside DisplayBitmap constructor");
    #endif
    display_bitmap = image;
    position_X = positionX;
    position_Y = positionY;
}

void DisplayBitmap::render(Display &display, unsigned short int current_menu_position)
{
    display.drawBitmap(
        position_X,
        position_Y,
        display_bitmap->data,
        display_bitmap->width,
        display_bitmap->height,
        SSD1306_WHITE
    );
    #ifdef DEBUG
    Serial.println((int)display_bitmap->data);
    Serial.println(display_bitmap->width);
    Serial.println(display_bitmap->height);
    Serial.println("finished bitmap render");
    #endif
}