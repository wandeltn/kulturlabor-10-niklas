#include <MainScreen.hpp>
#include <BitmapMainMenu.hpp>

void MainScreen::render(Display &display, unsigned short int current_menu_position) {
    display.clearDisplay();
    for(unsigned short int i = 0; i <= 8; i++)
    {
        if(i == current_menu_position) 
        {
            display.drawInvertBitmapColor(
                floor(i / 4) * 112,
                (i % 4) * 16,
                BitmapMainMenu::options_list[i],
                16,
                16,
                SSD1306_WHITE
            );
        } else {

            display.drawBitmap(
                floor(i / 4) * 112,
                (i % 4) * 16,
                BitmapMainMenu::options_list[i],
                16,
                16,
                SSD1306_WHITE
            );
        };
    };
    display.display();
};