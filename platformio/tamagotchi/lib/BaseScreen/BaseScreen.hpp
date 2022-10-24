#ifndef BaseScreen_H
#define BaseScreen_H

#include <Display.hpp>
#include <vector>
#include <Renderable.hpp>

class BaseScreen {
    public:
        BaseScreen(unsigned char max_menu_position);
        virtual ~BaseScreen();
        void render(Display &display);

        virtual void onButtonAPressed();
        virtual void onButtonBPressed() = 0;
        virtual void onButtonCPressed();

    protected:
        std::vector<Renderable*> render_list;
        unsigned short int current_menu_position;
        unsigned char max_menu_position_;
    private:
};

#endif