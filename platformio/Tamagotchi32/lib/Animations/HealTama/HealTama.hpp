#ifndef __HEALTAMA_H__
#define __HEALTAMA_H__

#include <BaseScreen.hpp>

class HealTama: public BaseScreen {
    public:
        HealTama(unsigned short menu_position, unsigned short frame_num = 0);
        void onButtonBPressed();
        void updateScreen();
    private:
        static short frameNumber;
        static short menuPosition;
        static unsigned long call_time;
};

#endif // __HEALTAMA_H__