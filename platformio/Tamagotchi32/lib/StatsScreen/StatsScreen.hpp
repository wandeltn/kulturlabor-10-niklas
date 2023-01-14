#ifndef __STATSSCREEN_H__
#define __STATSSCREEN_H__

#include <Renderable.hpp>

#include <BaseScreen.hpp>

class StatsScreen: public BaseScreen {
    public:
        StatsScreen();
        void onButtonBPressed();
    private:
};

#endif // __STATSSCREEN_H__