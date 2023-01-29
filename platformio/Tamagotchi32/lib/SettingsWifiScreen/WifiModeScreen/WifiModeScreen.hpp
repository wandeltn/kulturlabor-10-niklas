#ifndef __WIFIMODESCREEN_H__
#define __WIFIMODESCREEN_H__

#include <BaseScreen.hpp>
#include <WifiManager.hpp>

extern WifiManager wifiManager;

class WifiModeScreen: public BaseScreen {
    public:
        WifiModeScreen();
        void onButtonBPressed();
        void onButtonDPressed();
        inline static const char* display_options[2] = {
            "  Hotspot",
            "  Wifi"
        };
};

#endif // __WIFIMODESCREEN_H__