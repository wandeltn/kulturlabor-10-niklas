#include "UserInput.hpp"
#include <BaseScreen.hpp>
#include <Timer.hpp>
#include <Display.hpp>

#define BUTTON_A    D1
#define BUTTON_B    D6
#define BUTTON_C    D2

extern Timer timer;
extern bool schedule_rerender;
extern bool screen_on;
extern BaseScreen* active_screen;
extern Display display;

UserInput::UserInput() {
    attachInterrupt(digitalPinToInterrupt(BUTTON_A), onButtonAPressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_B), onButtonBPressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_C), onButtonCPressed, FALLING);

    timer.attach(screen_off_timer);
}

void UserInput::onButtonAPressed() {
    button_time = millis();
    if (button_time - last_button_time > 250)
    {
        active_screen->onButtonAPressed();
        resetScreenOff();
        screen_on = true;
        schedule_rerender = true;
        last_button_time = button_time;
    }
}

void UserInput::onButtonBPressed() {
        button_time = millis();
    if (button_time - last_button_time > 250)
    {
        if (screen_on) {
        button_B_pressed = true;
        }
        resetScreenOff();
        screen_on = true;
        last_button_time = button_time;
    }
}

void UserInput::onButtonCPressed() {
        button_time = millis();
    if (button_time - last_button_time > 250)
    {
        active_screen->onButtonCPressed();
        resetScreenOff();
        screen_on = true;
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

void UserInput::resetScreenOff()
{   
    if (screen_on) {
        timer.cancel(screen_off_timer);
        delete screen_off_timer;
    }
    screen_off_timer = new Timeable{ 
        .call_time = millis() + screen_off_time,
        .linked_value = &screen_off_times,
        .payload = 0,
        .notifier = &turnOffScreen
    };
    timer.attach(screen_off_timer);
}


unsigned long UserInput::last_button_time = 0;
unsigned long UserInput::button_time = 0;

unsigned short int UserInput::max_menu_position = 7;
unsigned short int UserInput::current_menu_position = 0;
unsigned short int UserInput::screen_off_time = 5000;

short int UserInput::screen_off_times = 0;
bool UserInput::button_B_pressed = false;
Timeable* UserInput::screen_off_timer = new Timeable{
    .call_time = millis() + screen_off_time,
    .linked_value = &screen_off_times,
    .payload = 0,
    .notifier = &turnOffScreen
};