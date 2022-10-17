#pragma once

#include <Button2.h>

#ifndef UserInput_H
#define UserInput_H

class UserInput 
{
    public:
        void begin();
        void loop();
        

    private:
        Button2 buttonA, buttonB, buttonC;

        static void onButtonAPressed(Button2& btn);
        static void onButtonBPressed(Button2& btn);
        static void onButtonCPressed(Button2& btn);
        
};

#endif