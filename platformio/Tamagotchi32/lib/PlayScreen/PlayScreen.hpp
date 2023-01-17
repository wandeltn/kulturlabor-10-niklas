#ifndef __PLAYSCREEN_H__
#define __PLAYSCREEN_H__

#include <BaseScreen.hpp>

class PlayScreen: public BaseScreen {
    public:
        PlayScreen();
        void onButtonBPressed();
        inline static const char* display_options[6] = {
        "  Soccer",
        "  Badminton",
        "  Hockey",
        "  Chess",
        "  Pong",
        "  Exit"
        };
    private:
};

#endif // __PLAYSCREEN_H__