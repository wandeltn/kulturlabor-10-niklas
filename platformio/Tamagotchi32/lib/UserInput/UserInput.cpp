#include <UMS3.h>
#include "UserInput.hpp"
#include <BaseScreen.hpp>
#include <Timer.hpp>
#include <Display.hpp>
#include <TamaStatus.hpp>

#define DEMO_MODE

#define BUTTON_A    0
#define BUTTON_B    13
#define BUTTON_C    14

extern Timer timer;
extern bool schedule_rerender;
extern bool screen_on;
extern BaseScreen* active_screen;
extern Display display;
extern TamaStatus tamaStatus;
extern UMS3 ums3;

UserInput::UserInput() {
}

void UserInput::begin()
{
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);

    attachInterrupt(12, onButtonAPressed, FALLING);
    attachInterrupt(13, onButtonBPressed, FALLING);
    attachInterrupt(14, onButtonCPressed, FALLING);
    ums3.setPixelColor(ums3.colorWheel(180));
}

void UserInput::onButtonAPressed() {
    Serial.println("Button A pressed!");
    button_time = millis();
    if (button_time - last_button_time > 250)
    {
        active_screen->onButtonAPressed();
        screen_on = true;
        #ifndef DEMO_MODE
        resetScreenOff();
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
        resetScreenOff();
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
        resetScreenOff();
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
void UserInput::resetScreenOff()
{   
    if (screen_on) {
        timer.cancel(screen_off_timer);
        delete screen_off_timer;
    } else {
        Serial.println("update position timer on screen on");
        tamaStatus.updatePositionTimer();
    }
    screen_off_timer = new Timeable{ 
        .call_time = millis() + screen_off_time,
        .linked_value = &screen_off_times,
        .payload = 0,
        .notifier = &turnOffScreen
    };
    timer.attach(screen_off_timer);
}
#endif


unsigned long UserInput::last_button_time = 0;
unsigned long UserInput::button_time = 0;

unsigned short int UserInput::max_menu_position = 7;
unsigned short int UserInput::current_menu_position = 0;
unsigned short int UserInput::screen_off_time = 5000;

short int UserInput::screen_off_times = 0;
bool UserInput::button_B_pressed = false;

#ifndef DEMO_MODE
Timeable* UserInput::screen_off_timer = new Timeable{
    .call_time = millis() + screen_off_time,
    .linked_value = &screen_off_times,
    .payload = 0,
    .notifier = &turnOffScreen
};
#endif