#ifndef __WIFICONNECT_H__
#define __WIFICONNECT_H__

#include <BaseScreen.hpp>

class WifiConnectScreen: public BaseScreen {
    public:
        WifiConnectScreen();
        void updateScreen();
        void onButtonBPressed(); 
        void onButtonDPressed(); 

    private:
        std::string on_screen_message;
};

#endif // __WIFICONNECT_H__