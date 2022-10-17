#include "UserInput.hpp"

#define BUTTON_A    D0
#define BUTTON_B    D6
#define BUTTON_C    D2


void ICACHE_RAM_ATTR UserInput::onButtonAPressed() {
    Serial.println("button A callback");
}

void ICACHE_RAM_ATTR UserInput::onButtonBPressed() {
    Serial.println("button B callback");
}

void ICACHE_RAM_ATTR UserInput::onButtonCPressed() {
    Serial.println("button C callback");
}


void UserInput::begin() {

}