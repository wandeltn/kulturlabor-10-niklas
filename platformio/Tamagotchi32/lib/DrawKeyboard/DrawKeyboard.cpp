#include <DrawKeyboard.hpp>
#include <Bitmaps.hpp>

DrawKeyboard::DrawKeyboard(): Renderable()
{

}

void DrawKeyboard::render(Display &display, unsigned short current_menu_position)
{
    for (unsigned int i = 0; i <= 24; i++) {
        if (i != current_menu_position)
        {
            display.drawBitmap(
                floor(i / 3) * 16,
                (i % 3) * 16,
                Bitmaps::Keyboard::Keyboard_images[i].data,
                Bitmaps::Keyboard::Keyboard_images[i].width,
                Bitmaps::Keyboard::Keyboard_images[i].height,
                SSD1306_WHITE
            );
        } else {
            display.drawInvertBitmapColor(
                floor(i / 3) * 16,
                (i % 3) * 16,
                Bitmaps::Keyboard::Keyboard_images[i].data,
                Bitmaps::Keyboard::Keyboard_images[i].width,
                Bitmaps::Keyboard::Keyboard_images[i].height,
                SSD1306_WHITE
            );
        }
    }
}

