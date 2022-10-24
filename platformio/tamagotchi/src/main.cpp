#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <cmath>
#include <vector>
#include <UserInput.hpp>
#include <BaseScreen.hpp>
#include <MainScreen.hpp>
#include <Display.hpp>
#include <Renderable.hpp>
#include <Timer.hpp>
#include <Timeable.hpp>
#include <TamaStatus.hpp>

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

Timer timer{};


static TamaStatus tamaStatus{};

BaseScreen* active_screen;

bool screen_on = true;
bool schedule_rerender = true;


static UserInput userInput;

void loop() {
    if (screen_on) {
        if(schedule_rerender) {
            display.clearDisplay();
            active_screen->render(display);
            display.display();
            schedule_rerender = false;
        } else if (userInput.button_B_pressed) {
            #ifdef DEBUG
            Serial.println("B pressed");
            #endif
            active_screen->onButtonBPressed();
            userInput.button_B_pressed = false;
            schedule_rerender = true;
        } else {
            timer.check_timer_list();
        }
    } else {
        timer.check_timer_list();
    }
}

void setup() {
    Serial.begin(9600);
    #ifdef DEBUG
    Serial.print("cpu freq: ");
    Serial.println(ESP.getCpuFreqMHz());
    Serial.print("heap free:");
    Serial.println(ESP.getFreeHeap());
    #endif

    pinMode(D1, INPUT_PULLUP);
    pinMode(D6, INPUT_PULLUP);
    pinMode(D2, INPUT_PULLUP);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
        #ifdef DEBUG
        Serial.println(F("SSD1306 allocation failed"));
        #endif
        for(;;); // Don't proceed, loop forever
    }    
    display.display();
    delay(1000);
    // Clear the buffer
    display.clearDisplay();
    display.dim(true);
    // init code
    active_screen = new MainScreen();

    display.display();    
}