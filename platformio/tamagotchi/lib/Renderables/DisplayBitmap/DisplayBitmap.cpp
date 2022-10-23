#include "DisplayBitmap/DisplayBitmap.hpp"
#include <Bitmaps.hpp>

DisplayBitmap::DisplayBitmap(const ImageFormat* image, unsigned short int positionX, unsigned short int positionY)
{
    Serial.println("inside DisplayBitmap constructor");
    display_bitmap = image;
    position_X = positionX;
    position_Y = positionY;
}

void DisplayBitmap::render(Display &display, unsigned short int current_menu_position)
{
    display.drawBitmap(
        0,
        0,
        Bitmaps::attention_menu_icon,
        display_bitmap->width,
        display_bitmap->length,
        SSD1306_WHITE
    );
    Serial.println((int)display_bitmap->data);
    Serial.println(display_bitmap->width);
    Serial.println(display_bitmap->height);
    Serial.println("finished bitmap render");
}