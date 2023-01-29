#ifndef __SETTINGSWIFISCREEN_H__
#define __SETTINGSWIFISCREEN_H__

#include <BaseScreen.hpp>

class WifiSettingsScreen: public BaseScreen {
    public:
        WifiSettingsScreen();
        void onButtonBPressed();
        inline static const char* display_options[6] {
            "  Connect",
            "  Mode"
            "  Edit",
            "  Add",
            "  Remove",
            "  Info",
        };
};

#endif // __SETTINGSWIFISCREEN_H__