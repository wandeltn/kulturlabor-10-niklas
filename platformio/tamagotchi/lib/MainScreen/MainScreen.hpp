#ifndef MainScreen_H
#define MainScreen_H

#include <Renderable.hpp>
#include <BaseScreen.hpp>


class MainScreen: public BaseScreen {
    public:
        MainScreen();
        void onButtonBPressed(unsigned short int current_menu_position);
    private:

};

#endif