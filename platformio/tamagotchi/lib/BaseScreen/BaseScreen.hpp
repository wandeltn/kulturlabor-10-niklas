#ifndef BaseScreen_H
#define BaseScreen_H

#include <Display.hpp>

class BaseScreen {
    public:
    BaseScreen();
        virtual void render(Display &display, unsigned short int current_menu_position);
};

#endif