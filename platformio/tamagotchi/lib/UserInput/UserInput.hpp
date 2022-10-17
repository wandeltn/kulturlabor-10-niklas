#pragma once

#ifndef UserInput_H
#define UserInput_H

#include <SPI.h>

class UserInput 
{
    public:
        void begin();

        void ICACHE_RAM_ATTR onButtonAPressed();
        void ICACHE_RAM_ATTR onButtonBPressed();
        void ICACHE_RAM_ATTR onButtonCPressed();

    private:
        
};

#endif