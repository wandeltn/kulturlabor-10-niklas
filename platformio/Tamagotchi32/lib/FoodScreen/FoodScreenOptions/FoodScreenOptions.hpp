#ifndef FoodScreenOptions_H
#define FoodScreenOptions_H

#include <Renderable.hpp>

class FoodScreenOptions: public Renderable {
    public:
        FoodScreenOptions();
        void onButtonBPressed(unsigned short int current_menu_position);
        void render(Display& display, unsigned short int current_menu_position);
    private:

};

#endif