#ifndef SubMenu_H
#define SubMenu_H

#include <Renderable.hpp>

class SubMenu: Renderable {
    public:
        virtual void selectCurrentOption(unsigned short int current_menu_position);
        virtual void render(Display &display, unsigned short int current_menu_position);   

    private:
};

#endif