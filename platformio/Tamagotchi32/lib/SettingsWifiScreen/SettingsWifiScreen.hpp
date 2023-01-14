#ifndef __SETTINGSWIFISCREEN_H__
#define __SETTINGSWIFISCREEN_H__

#include <BaseScreen.hpp>

class SettingsWifiScreen: public BaseScreen {
    public:
        SettingsWifiScreen();
        void onButtonBPressed();
        inline static const char* display_options[6] {
            "  Connect",
            "  Edit",
            "  Add",
            "  Remove",
            "  Info",
            "  Cancel"
        };
};

#endif // __SETTINGSWIFISCREEN_H__