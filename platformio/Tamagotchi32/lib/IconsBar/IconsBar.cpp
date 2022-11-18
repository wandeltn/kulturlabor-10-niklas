#include <IconsBar.hpp>
#include <Bitmaps.hpp>
#include <TamaStatus.hpp>

extern TamaStatus tamaStatus;

IconsBar::IconsBar(const ImageFormat* image, short int* amount, unsigned short int positionX)
{
    #ifdef DEBUG
    Serial.println("inside IconsBar constructor");
    #endif
    display_bitmap = image;
    position_X = positionX;
    icon_amount = amount;
    convert_value = false;
}

IconsBar::IconsBar(const ImageFormat* image, short int* amount, unsigned short int positionX, bool convert)
{
    #ifdef DEBUG
    Serial.println("inside IconsBar constructor");
    #endif
    display_bitmap = image;
    position_X = positionX;
    icon_amount = amount;
    convert_value = convert;
}

void IconsBar::render(Display &display, unsigned short int current_menu_position)
{   
    if (convert_value) {
        for (unsigned short int icon_index = 0; icon_index < *icon_amount / 100.0 * 8; icon_index++) {

            display.drawBitmap(
                position_X,
                icon_index * 8,
                display_bitmap->data,
                display_bitmap->width,
                display_bitmap->height,
                SSD1306_WHITE
            );
        }
    } else{
        for (unsigned short int icon_index = 0; icon_index < *icon_amount; icon_index++) {

            display.drawBitmap(
                position_X,
                icon_index * 8,
                display_bitmap->data,
                display_bitmap->width,
                display_bitmap->height,
                SSD1306_WHITE
            );
        }
    }
}
