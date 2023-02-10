#ifndef __PLAYBADMINTON_H__
#define __PLAYBADMINTON_H__

#include <BaseScreen.hpp>
#include <Vector2.hpp>

class PlayBadminton: public BaseScreen {
    public: 
        PlayBadminton();
        void updateScreen();
        void onButtonAPressed();
        void onButtonBPressed();
        void onButtonCPressed();
        void onButtonDPressed();
    
    private:
        Vector2 current_player_position;
        Vector2 current_ball_position;
        Vector2 ball_destination;
        unsigned long call_time;
};

#endif // __PLAYBADMINTON_H__