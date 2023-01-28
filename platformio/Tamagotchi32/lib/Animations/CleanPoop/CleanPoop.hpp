#ifndef __CLEANPOOP_H__
#define __CLEANPOOP_H__

#include <BaseScreen.hpp>

class CleanPoop: public BaseScreen {
    public:
        CleanPoop(unsigned short menu_item, unsigned short frame_num);
        void onButtonBPressed();
        void updateScreen();

    private:
        static unsigned short frameNumber;
        static short menuItem;
        unsigned long call_time;

};

#endif // __CLEANPOOP_H__