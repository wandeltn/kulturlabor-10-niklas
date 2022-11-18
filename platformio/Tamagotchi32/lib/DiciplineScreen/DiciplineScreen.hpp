#ifndef __DICIPLINESCREEN_H__
#define __DICIPLINESCREEN_H__

#include <BaseScreen.hpp>

class DiciplineScreen: public BaseScreen {
    public:
        DiciplineScreen();
        void onButtonBPressed();
        static const char* display_options[5];
    private:
};

#endif // __DICIPLINESCREEN_H__