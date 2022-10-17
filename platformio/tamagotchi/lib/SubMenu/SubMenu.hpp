#ifndef DisplayMenu_H
#define DisplayMenu_H

#include <Adafruit_SSD1306.h>
#include <Renderable.hpp>
#include <vector>

using namespace std;

class SubMenu {
    public:
        virtual void onMenuPositionChanged();
        virtual void drawCurrentStats();
        
        void onButtonAPressed();
        virtual void onButtonBPressed();
        void onButtonCPressed();

        void render(Adafruit_SSD1306 &display);

    private:
        unsigned short int current_menu_position;
        unsigned short int max_menu_position;
};

#endif