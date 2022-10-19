#include <SPI.h>
#include <Wire.h>
#include <cmath>
#include <vector>
#include <SubMenu.hpp>
#include <UserInput.hpp>
#include <BaseScreen.hpp>
#include <MainScreen.hpp>
#include <Display.hpp>
#include <Renderable.hpp>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  D7
#define OLED_CLK   D5
#define OLED_DC    D0
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

static UserInput userInput;


BaseScreen* active_screen;

void loop() {
    if(userInput.last_menu_positon != userInput.current_menu_position) {
        display.clearDisplay();
        active_screen->render(display, userInput.current_menu_position);
        display.display();
        userInput.last_menu_positon = userInput.current_menu_position;
    } else if (userInput.button_B_pressed) {
        
    }
}

void setup() {
    Serial.begin(9600);

    pinMode(D1, INPUT_PULLUP);
    pinMode(D6, INPUT_PULLUP);
    pinMode(D2, INPUT_PULLUP);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }    
    display.display();
    delay(1000);
    // Clear the buffer
    display.clearDisplay();

    // init code
    active_screen = new MainScreen();

    display.display();    
}