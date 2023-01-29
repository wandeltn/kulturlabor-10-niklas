#pragma once

#ifndef UserInput_H
#define UserInput_H

#include <SPI.h>
#include <Timeable.hpp>

class UserInput 
{
    public:
        UserInput();

        static void begin();

        static unsigned long last_button_time;
        static unsigned long button_time;
        static short linked_value;
        static unsigned short int max_menu_position;
        static unsigned short int current_menu_position;

        static bool button_B_pressed;

        static void ARDUINO_ISR_ATTR onButtonAPressed();
        static void ARDUINO_ISR_ATTR onButtonBPressed();
        static void ARDUINO_ISR_ATTR onButtonCPressed();

        static void turnOffScreen();
        static void resetScreenOff(bool);
    private:
        static Timeable* screen_off_timer;
};

#endif