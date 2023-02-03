#ifndef __PLAYSOCCER_H__
#define __PLAYSOCCER_H__

#include <BaseScreen.hpp>

class PlaySoccer: public BaseScreen {
    public:
        PlaySoccer();
        void updateScreen();
        void onButtonBPressed();
        void onButtonDPressed();

    private:
        uint8_t current_line_position;
        bool moving_down;
        unsigned long call_time;
};

#endif // __PLAYSOCCER_H__