#ifndef __POOPSCREEN_H__
#define __POOPSCREEN_H__

#include <BaseScreen.hpp>

class PoopScreen: public BaseScreen {
    public:
        PoopScreen();
        void onButtonBPressed();
        inline static const char* display_options[2] = {
        "  Clean poop",
        "  Exit"
        };
    private:
};

#endif // __POOPSCREEN_H__