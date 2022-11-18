#pragma once

#ifndef UserInput_H
#define UserInput_H

#include <SPI.h>
#include <Timeable.hpp>

class UserInput 
{
    public:
        UserInput();

        static unsigned long last_button_time;
        static unsigned long button_time;

        static unsigned short int max_menu_position;
        static unsigned short int current_menu_position;
        static unsigned short int screen_off_time;
        static short int screen_off_times;        

        static bool button_B_pressed;

        static void IRAM_ATTR onButtonAPressed();
        static void IRAM_ATTR onButtonBPressed();
        static void IRAM_ATTR onButtonCPressed();

        static void turnOffScreen();
        static void resetScreenOff();
    private:
        static Timeable* screen_off_timer;
};

#endif