#include <SPI.h>
#include <Wire.h>
#include <cmath>
#include <SubMenu.hpp>
#include <BitmapMainMenu.hpp>
#include <Display.hpp>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  D7
#define OLED_CLK   D5
#define OLED_DC    D1
#define OLED_CS    D8
#define OLED_RESET D4
Display display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    OLED_MOSI,
    OLED_CLK,
    OLED_DC,
    OLED_RESET,
    OLED_CS
);

BitmapMainMenu MainMenuIcons;

int current_menu_position;
int max_menu_position;


void loop() {
}

void setup() {
    Serial.begin(9600);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }    
    // Clear the buffer
    display.clearDisplay();

    current_menu_position = 3;
    max_menu_position = 8;

    for(unsigned short int i = 0; i <= max_menu_position; i++)
    {
        if(i == current_menu_position) 
        {
            display.drawInvertBitmapColor(
                floor(i / 4) * 112,
                (i % 4) * 16,
                MainMenuIcons.medicine_menu_icon,
                16,
                16,
                SSD1306_WHITE
            );
        } else {
            display.drawBitmap(
                floor(i / 4) * 112,
                (i % 4) * 16,
                MainMenuIcons.medicine_menu_icon,
                16,
                16,
                SSD1306_WHITE
            );
        };
    };

    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(2000);

    
}