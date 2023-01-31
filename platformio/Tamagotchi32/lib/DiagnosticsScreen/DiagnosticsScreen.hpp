#ifndef __DIAGNOSTICSSCREEN_H__
#define __DIAGNOSTICSSCREEN_H__

#include <BaseScreen.hpp>

class DiagnosticsScreen: public BaseScreen {
    public: 
        DiagnosticsScreen();
        void onButtonBPressed();
        void onButtonDPressed();
        void updateScreen();
};

#endif // __DIAGNOSTICSSCREEN_H__