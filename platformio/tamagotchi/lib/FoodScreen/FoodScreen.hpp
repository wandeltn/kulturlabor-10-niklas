#ifndef FoodScreen_H
#define FoodScreen_H

#include <BaseScreen.hpp>

class FoodScreen: public BaseScreen {
    public:
        FoodScreen();
        void onButtonBPressed();
        inline static const char* display_options[8] = {
        "  Burger",
        "  Pasta",
        "  Muffin",
        "  Broccoli",
        "  Salad",
        "  Sushi",
        "  Crepes",
        "  Exit"
        };
    private:
};

#endif