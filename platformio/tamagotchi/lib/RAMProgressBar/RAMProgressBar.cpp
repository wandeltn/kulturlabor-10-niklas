#include <RAMProgressBar.hpp>
#include <string>
#include <ESP8266WiFi.h>


RAMProgressBar::RAMProgressBar(
            unsigned short int x,
            unsigned short int y,
            unsigned short int w,
            unsigned short int h)
{
    Serial.println("inside RAMProgressBar constructor");
    positionX = x;
    positionY = y;
    width = w;
    height = h;
}

void RAMProgressBar::render(Display& display, unsigned short int current_menu_position)
{
    Serial.println("inside render RAMProgressBar");
    display.drawRect(
        positionX,
        positionY,
        width,
        height,
        SSD1306_WHITE
    );
    Serial.print("RAM bar fill height: ");
    Serial.println(ESP.getFreeHeap() / 81920.0 * width);
    display.fillRect(
        positionX,
        positionY,
        round(ESP.getFreeHeap() / 81920.0 * width),
        height,
        SSD1306_WHITE
    );

    Serial.println("exiting render RAMProgressBar");
}

void RAMProgressBar::selectCurrentOption(unsigned short int current_menu_position)
{
    
}


unsigned short int RAMProgressBar::positionX = 0;
unsigned short int RAMProgressBar::positionY = 0;
unsigned short int RAMProgressBar::width = 0;
unsigned short int RAMProgressBar::height = 0;
