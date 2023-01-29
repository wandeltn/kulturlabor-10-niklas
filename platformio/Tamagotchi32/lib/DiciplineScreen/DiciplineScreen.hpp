#ifndef __DICIPLINESCREEN_H__
#define __DICIPLINESCREEN_H__

#include <BaseScreen.hpp>

class DiciplineScreen: public BaseScreen {
    public:
        DiciplineScreen();
        void onButtonBPressed();
        inline static const char* display_options[4] = {
            "  Time together",
            "  Set expectations",
            "  Use concequences",
            "  Do an activity"
        };
    private:
};

#endif // __DICIPLINESCREEN_H__