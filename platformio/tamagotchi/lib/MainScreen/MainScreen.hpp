#ifndef MainScreen_H
#define MainScreen_H

#include <Renderable.hpp>
#include <BaseScreen.hpp>


class MainScreen: public Renderable, public BaseScreen {
    public:
        void render(Display display, unsigned short int current_menu_position);
    private:

};

#endif