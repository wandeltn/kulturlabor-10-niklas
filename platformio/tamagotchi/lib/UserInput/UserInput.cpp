#include "UserInput.hpp"

#define BUTTON_A    D1
#define BUTTON_B    D6
#define BUTTON_C    D2

UserInput::UserInput() {
    attachInterrupt(digitalPinToInterrupt(BUTTON_A), onButtonAPressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_B), onButtonBPressed, LOW);
    attachInterrupt(digitalPinToInterrupt(BUTTON_C), onButtonCPressed, LOW);
}

void UserInput::onButtonAPressed() {
    button_time = millis();
    if (button_time - last_button_time > 250)
    {
        Serial.println(++current_menu_position);
        last_button_time = button_time;
    }
}

void IRAM_ATTR UserInput::onButtonBPressed() {
    Serial.println("button B callback");
}

void IRAM_ATTR UserInput::onButtonCPressed() {
        button_time = millis();
    if (button_time - last_button_time > 250)
    {
        Serial.println(--current_menu_position);
        last_button_time = button_time;
    }
}


unsigned long UserInput::button_time = 0;
unsigned long UserInput::last_button_time = 0;

unsigned short int UserInput::current_menu_position = 0;
unsigned short int UserInput::max_menu_position = 7;
unsigned short int UserInput::last_menu_positon = 0;