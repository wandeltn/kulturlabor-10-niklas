#include <UserInput.hpp>
#include <DisplayMenu.hpp>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  D7
#define OLED_CLK   D5
#define OLED_DC    D1
#define OLED_CS    D8
#define OLED_RESET D4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

UserInput UI;
DisplayMenu displayMenu;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(D0, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    UI.begin();
}

void loop() {
    // put your main code here, to run repeatedly:
    //UI.loop();
    displayMenu.render(display);
}