#ifndef FoodScreen_H
#define FoodScreen_H

#include <BaseScreen.hpp>

class FoodScreen: public BaseScreen {
    public:
        FoodScreen();
        void onButtonBPressed(unsigned short int current_menu_position);
    private:

};

#endif