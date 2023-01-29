#ifndef __WIFICONNECT_H__
#define __WIFICONNECT_H__

#include <BaseScreen.hpp>

class WifiConnectScreen: public BaseScreen {
    public:
        WifiConnectScreen();
        void onButtonBPressed(); 
        void onButtonDPressed(); 
};

#endif // __WIFICONNECT_H__