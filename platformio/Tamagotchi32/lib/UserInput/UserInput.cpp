#include <UMS3.h>
#include "UserInput.hpp"
#include <BaseScreen.hpp>
#include <Timer.hpp>
#include <Display.hpp>
#include <TamaStatus.hpp>

// #define DEMO_MODE

#define BUTTON_A        12
#define BUTTON_B        13
#define BUTTON_C        14
#define BUTTON_D        15
#define SCREEN_OFF_TIME 15

extern Timer timer;
extern bool schedule_rerender;
extern bool screen_on;
extern BaseScreen* active_screen;
extern Display display;
extern TamaStatus tamaStatus;
extern UMS3 ums3;
extern struct timeval tv;

UserInput::UserInput() {
    resetScreenOff(true);
}

void UserInput::begin()
{
    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    pinMode(BUTTON_D, INPUT_PULLUP);

    ums3.setPixelColor(ums3.colorWheel(180));
    
    attachInterrupt(BUTTON_A, onButtonAPressed, FALLING);
    attachInterrupt(BUTTON_B, onButtonBPressed, FALLING);
    attachInterrupt(BUTTON_C, onButtonCPressed, FALLING);
    attachInterrupt(BUTTON_D, onButtonDPressed, FALLING);

    struct timeval tv_;
    gettimeofday(&tv_, NULL);
    screen_off_timer = new Timeable{
        .call_time = (unsigned long)tv_.tv_sec + SCREEN_OFF_TIME,
        .linked_value = &linked_value,
        .payload = 0,
        .notifier = &turnOffScreen
    };
    timer.attach(screen_off_timer);
}

void UserInput::onButtonAPressed() {
    Serial.println("Button A pressed!");
    button_time = millis();
    if (button_time - last_button_time > 250)
    {
        active_screen->onButtonAPressed();
        screen_on = true;
        #ifndef DEMO_MODE
        resetScreenOff(false);
        #endif
        schedule_rerender = true;
        last_button_time = button_time;
    }
}

void UserInput::onButtonBPressed() {
    Serial.println("Button A pressed!");
    button_time = millis();
    if (button_time - last_button_time > 250)
    {
        if (screen_on) {
            button_B_pressed = true;
        }
        screen_on = true;
        #ifndef DEMO_MODE
        resetScreenOff(false);
        #endif
        last_button_time = button_time;
    }
}

void UserInput::onButtonCPressed() {
    Serial.println("Button A pressed!");
    button_time = millis();
    if (button_time - last_button_time > 250)
    {
        active_screen->onButtonCPressed();
        screen_on = true;
        #ifndef DEMO_MODE
        resetScreenOff(false);
        #endif
        schedule_rerender = true;
        last_button_time = button_time;
    }
}

void ARDUINO_ISR_ATTR UserInput::onButtonDPressed()
{
    Serial.println("Button D pressed!");
    button_time = millis();
    if (button_time - last_button_time > 250)
    {
        active_screen->onButtonDPressed();
        #ifndef DEMO_MODE
        resetScreenOff(false);
        #endif
        schedule_rerender = true;
        last_button_time = button_time;
    }    
}

void UserInput::turnOffScreen()
{
    screen_on = false;
    display.clearDisplay();
    display.display();
}

#ifndef DEMO_MODE
void UserInput::resetScreenOff(bool initTimer = false)
{   
    if (!initTimer) {
        if (screen_on) {
            timer.cancel(screen_off_timer);
            delete screen_off_timer;
        } else {
            Serial.println("update position timer on screen on");
        }
    }
    screen_off_timer = new Timeable{
        .call_time = (unsigned long)tv.tv_sec + SCREEN_OFF_TIME,
        .linked_value = &linked_value,
        .payload = 0,
        .notifier = &turnOffScreen
    };
    timer.attach(screen_off_timer);
}
#endif


unsigned long UserInput::last_button_time = 0;
unsigned long UserInput::button_time = 0;
short UserInput::linked_value = 0;
unsigned short int UserInput::max_menu_position = 7;
unsigned short int UserInput::current_menu_position = 0;

bool UserInput::button_B_pressed = false;

#ifndef DEMO_MODE
Timeable* UserInput::screen_off_timer = new Timeable{
    .call_time = SCREEN_OFF_TIME,
    .linked_value = &linked_value,
    .payload = 0,
    .notifier = &turnOffScreen
};
#endif