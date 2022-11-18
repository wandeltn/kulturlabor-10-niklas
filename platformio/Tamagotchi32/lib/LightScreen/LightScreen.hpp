#ifndef __LIGHTSCREEN_H__
#define __LIGHTSCREEN_H__

#include <BaseScreen.hpp>

class LightScreen: public BaseScreen {
    public:
        LightScreen();
        void onButtonBPressed();
        inline static const char* display_options[3] = {
            "  Light ON",
            "  Light OFF",
            "  Exit"
        };
};

#endif // __LIGHTSCREEN_H__