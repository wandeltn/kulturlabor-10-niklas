#pragma once

#ifndef UserInput_H
#define UserInput_H

#include <SPI.h>

class UserInput 
{
    public:
        UserInput();

        static unsigned long last_button_time;
        static unsigned long button_time;

        static unsigned short int max_menu_position;
        static unsigned short int current_menu_position;
        static unsigned short int last_menu_positon;

        static bool button_B_pressed;

        static void onButtonAPressed() IRAM_ATTR;
        static void onButtonBPressed() IRAM_ATTR;
        static void onButtonCPressed() IRAM_ATTR;

    private:
    
};

#endif