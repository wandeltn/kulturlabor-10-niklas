#ifndef __KEYBOARDSCREEN_H__
#define __KEYBOARDSCREEN_H__

#include <BaseScreen.hpp>

class KeyboardScreen: public BaseScreen {
    public:
        KeyboardScreen(std::string output_string, BaseScreen* return_screen);
        void onButtonBPressed();
        void onButtonDPressed();

    private:
        std::string output_string_;
        BaseScreen* return_screen_;
};

#endif // __KEYBOARDSCREEN_H__