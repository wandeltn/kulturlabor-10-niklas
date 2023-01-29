#ifndef __FEEDTAMA_H__
#define __FEEDTAMA_H__

#include <BaseScreen.hpp>

class FeedTama: public BaseScreen {
    public:
        FeedTama(unsigned short food_item, unsigned short frame_num);
        void onButtonBPressed();
        void updateScreen();

    private:
        static short frameNumber;
        static short foodItem;
        unsigned long call_time;

};

#endif // __FEEDTAMA_H__