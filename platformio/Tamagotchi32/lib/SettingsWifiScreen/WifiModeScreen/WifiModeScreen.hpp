#ifndef __WIFIMODESCREEN_H__
#define __WIFIMODESCREEN_H__

#include <BaseScreen.hpp>
#include <WifiManager.hpp>

extern WifiManager wifiManager;

class WifiModeScreen: public BaseScreen {
    public:
        WifiModeScreen();
        void onButtonBPressed();
        inline static const char* display_options[3] = {
            "  Hotspot",
            "  Wifi",
            "  Cancel"
        };
};

#endif // __WIFIMODESCREEN_H__