#ifndef __PLAYTAMA_H__
#define __PLAYTAMA_H__

#include <BaseScreen.hpp>

class PlayTama: public BaseScreen {
    public:
        PlayTama(short play_action, short frame_number);
        void onButtonBPressed();
        void updateScreen();

        static short frameNumber;
        static short playAction;

    private:
        unsigned long call_time;
};

#endif // __PLAYTAMA_H__