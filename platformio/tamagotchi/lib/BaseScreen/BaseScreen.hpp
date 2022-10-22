#ifndef BaseScreen_H
#define BaseScreen_H

#include <Display.hpp>
#include <vector>
#include <Renderable.hpp>

class BaseScreen {
    public:
        BaseScreen();
        void render(Display &display, unsigned short int current_menu_position);
        virtual void onButtonBPressed(unsigned short int current_menu_position) = 0;
    
    protected:
        std::vector<Renderable*> render_list;

    private:
};

#endif