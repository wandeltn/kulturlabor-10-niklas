#include <SPI.h>
#include <Wire.h>
#include <SPI.h>
#include <Wire.h>
#include <UMS3.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Test");
}

#include <SPI.h>
#include <Wire.h>
#include <UMS3.h>
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

#define DEBUG

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  35
#define OLED_CLK   36
#define OLED_DC    6
#define OLED_CS    34
#define OLED_RESET 7
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

UMS3 ums3;

static TamaStatus tamaStatus{};

BaseScreen* active_screen;

bool screen_on = true;
bool schedule_rerender = true;


static UserInput userInput;

void loop() {
    Serial.println("at start of loop in main");
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
    Serial.begin(115200);
    ums3.begin();
    #ifdef DEBUG
    Serial.print("cpu freq: ");
    Serial.println(ESP.getCpuFreqMHz());
    Serial.print("heap free:");
    Serial.println(ESP.getFreeHeap());
    #endif

    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);

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