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
#include <Timer.hpp>
#include <Timeable.hpp>


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

Timer timer{};
BaseScreen* active_screen;

bool schedule_rerender;
short int test_value = 0;

Timeable test_timer{
    call_time: 10,
    linked_value: &test_value,
    payload: 5
};

void loop() {
    if(schedule_rerender) {
        display.clearDisplay();
        active_screen->render(display, userInput.current_menu_position);
        display.display();
        schedule_rerender = false;
    } else if (userInput.button_B_pressed) {
        Serial.println("B pressed");
        active_screen->onButtonBPressed(userInput.current_menu_position);
        userInput.button_B_pressed = false;
        schedule_rerender = true;
    } else {
        timer.check_timer_list();
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
    timer.attach(&test_timer);
    schedule_rerender = true;

    display.display();    
}