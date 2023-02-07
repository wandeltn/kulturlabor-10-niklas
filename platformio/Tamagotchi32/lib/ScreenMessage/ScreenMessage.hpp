#ifndef __SCREENMESSAGE_H__
#define __SCREENMESSAGE_H__

#include <BaseScreen.hpp>

class ScreenMessage: public BaseScreen {
    public:
        ScreenMessage(std::string* display_text, BaseScreen* return_screen);
        ScreenMessage(std::string display_text, BaseScreen* return_screen);
        void onButtonBPressed();
        void onButtonDPressed();

    private:
        std::string display_text_;
        BaseScreen* return_screen_;
};

#endif // __SCREENMESSAGE_H__