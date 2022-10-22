#include "UserInput.hpp"
#include <BaseScreen.hpp>

#define BUTTON_A    D1
#define BUTTON_B    D6
#define BUTTON_C    D2

extern bool schedule_rerender;
extern BaseScreen* active_screen;

UserInput::UserInput() {
    attachInterrupt(digitalPinToInterrupt(BUTTON_A), onButtonAPressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_B), onButtonBPressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_C), onButtonCPressed, FALLING);
}

void UserInput::onButtonAPressed() {
    button_time = millis();
    if (button_time - last_button_time > 250)
    {
        active_screen->onButtonAPressed();
        schedule_rerender = true;
        last_button_time = button_time;
    }
}

void UserInput::onButtonBPressed() {
        button_time = millis();
    if (button_time - last_button_time > 250)
    {
        button_B_pressed = true;
        last_button_time = button_time;
    }
}

void UserInput::onButtonCPressed() {
        button_time = millis();
    if (button_time - last_button_time > 250)
    {
        active_screen->onButtonCPressed();
        last_button_time = button_time;
        schedule_rerender = true;
    }
}


unsigned long UserInput::last_button_time = 0;
unsigned long UserInput::button_time = 0;

unsigned short int UserInput::max_menu_position = 7;
unsigned short int UserInput::current_menu_position = 0;
unsigned short int UserInput::last_menu_positon = 1;

bool UserInput::button_B_pressed = false;