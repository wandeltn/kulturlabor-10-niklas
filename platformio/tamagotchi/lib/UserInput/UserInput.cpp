#include "UserInput.hpp"



void UserInput::onButtonAPressed(Button2& btn) {
    Serial.println("button A callback");
}

void UserInput::onButtonBPressed(Button2& btn) {
    Serial.println("button B callback");
}

void UserInput::onButtonCPressed(Button2& btn) {
    Serial.println("button C callback");
}


void UserInput::begin() {
    buttonA.begin(D0, 2U, false, false);
    buttonA.setClickHandler(onButtonAPressed);

    buttonB.begin(D6, 2U, false, false);
    buttonB.setClickHandler(onButtonBPressed);
    
    buttonC.begin(D2, 2U, false, false);
    buttonC.setClickHandler(onButtonCPressed);
}

void UserInput::loop() {
    buttonA.loop();
    buttonB.loop();
    buttonC.loop();
}