#include <RAMProgressBar.hpp>
#include <string>
#include <ESP8266WiFi.h>


RAMProgressBar::RAMProgressBar(
            unsigned short int x,
            unsigned short int y,
            unsigned short int w,
            unsigned short int h)
{
    #ifdef DEBUG
    Serial.println("inside RAMProgressBar constructor");
    #endif
    positionX = x;
    positionY = y;
    width = w;
    height = h;
}

void RAMProgressBar::render(Display& display, unsigned short int current_menu_position)
{
    #ifdef DEBUG
    Serial.println("inside render RAMProgressBar");
    #endif
    display.drawRect(
        positionX,
        positionY,
        width,
        height,
        SSD1306_WHITE
    );
    #ifdef DEBUG
    Serial.print("RAM bar fill height: ");
    Serial.println(ESP.getFreeHeap() / 81920.0 * width);
    #endif
    display.fillRect(
        positionX,
        positionY,
        round(ESP.getFreeHeap() / 81920.0 * width),
        height,
        SSD1306_WHITE
    );

    #ifdef DEBUG
    Serial.println("exiting render RAMProgressBar");
    #endif
}


unsigned short int RAMProgressBar::positionX = 0;
unsigned short int RAMProgressBar::positionY = 0;
unsigned short int RAMProgressBar::width = 0;
unsigned short int RAMProgressBar::height = 0;
