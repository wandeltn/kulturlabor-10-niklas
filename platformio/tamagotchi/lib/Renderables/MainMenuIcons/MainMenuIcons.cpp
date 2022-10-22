#include "./MainMenuIcons.hpp"
#include <Bitmaps.hpp>

void MainMenuIcons::selectCurrentOption(unsigned short int current_menu_position) {

}

void MainMenuIcons::render(Display &display, unsigned short int current_menu_position) {
    for(unsigned short int i = 0; i <= 8; i++)
    {
        if(i == current_menu_position) 
        {
            display.drawInvertBitmapColor(
                floor(i / 4) * 112,
                (i % 4) * 16,
                Bitmaps::options_list[i],
                16,
                16,
                SSD1306_WHITE
            );
        } else {

            display.drawBitmap(
                floor(i / 4) * 112,
                (i % 4) * 16,
                Bitmaps::options_list[i],
                16,
                16,
                SSD1306_WHITE
            );
        };
    };
    Serial.println("mainscreen rendered");
}