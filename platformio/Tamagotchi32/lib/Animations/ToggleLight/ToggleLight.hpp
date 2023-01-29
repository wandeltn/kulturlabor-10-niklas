#ifndef __TOGGLELIGHT_H__
#define __TOGGLELIGHT_H__

#include <BaseScreen.hpp>
#include <Timeable.hpp>

class ToggleLight: public BaseScreen {
    public:
        ToggleLight(bool, unsigned short);
        void onButtonBPressed();
        void updateScreen();

        static int16_t frameNumber;
        static bool lightOn;
        
    private:
        unsigned long call_time;
};

#endif // __TOGGLELIGHT_H__