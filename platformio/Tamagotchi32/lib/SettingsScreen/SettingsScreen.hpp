#ifndef __SETTINGSSCREEN_H__
#define __SETTINGSSCREEN_H__

#include <BaseScreen.hpp>

class SettingsScreen: public BaseScreen {
    public:
        SettingsScreen();
        void onButtonBPressed();
        inline static const char* display_options[4] = {
            "  Rename Tama",
            "  Wifi Settings",
            "  Diagnostics",
            "  RESET"
        };

};


#endif // __SETTINGSSCREEN_H__