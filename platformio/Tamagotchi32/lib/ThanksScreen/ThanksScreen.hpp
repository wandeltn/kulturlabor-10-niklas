#ifndef __THANKSSCREEN_H__
#define __THANKSSCREEN_H__

#include <BaseScreen.hpp>

class ThanksScreen: public BaseScreen {
    public: 
        ThanksScreen();
        void onButtonBPressed();
        
    private:
        std::string display_text = "Ich hab dich lieb Andromeda ;-) Vielen Dank das du fuer mich da warst";
};

#endif // __THANKSSCREEN_H__