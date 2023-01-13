#ifndef __RESETSCREEN_H__
#define __RESETSCREEN_H__

#include <BaseScreen.hpp>

class ResetScreen: public BaseScreen {
    public: 
        ResetScreen();
        void onButtonBPressed();
        inline static const char* display_options[] = {
            "  Reset",
            "  Cancel"
        };
};

#endif // __RESETSCREEN_H__