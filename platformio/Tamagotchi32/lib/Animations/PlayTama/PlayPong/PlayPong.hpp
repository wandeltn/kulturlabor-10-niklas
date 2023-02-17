#ifndef __PLAYPONG_H__
#define __PLAYPONG_H__

#include <BaseScreen.hpp>
#include <Vector2.hpp>

class PlayPong: public BaseScreen {
    public:
        PlayPong();
        void updateScreen();
        void onButtonAPressed();
        void onButtonBPressed();
        void onButtonDPressed();

    private:
        int_fast8_t current_player_position;
        int_fast8_t current_bot_position;
        Vector2 current_ball_position;
        unsigned long call_time;
};

#endif // __PLAYPONG_H__