#pragma once

#ifndef DisplayMenu_H
#define DisplayMenu_H

#include <Adafruit_SSD1306.h>
#include <Renderable.hpp>
#include <vector>

using namespace std;

class DisplayMenu {
    public:
        virtual void onMenuPositionChanged();
        virtual void drawCurrentStats();
        
        void onButtonAPressed();
        virtual void onButtonBPressed();
        void onButtonCPressed();

        void render(Adafruit_SSD1306 &display);
        void testdrawbitmap(Adafruit_SSD1306 &display);

    private:
        vector<Renderable> render_list;
        
};

#endif