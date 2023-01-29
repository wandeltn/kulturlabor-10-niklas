#ifndef __DISPLAYFASTLINE_H__
#define __DISPLAYFASTLINE_H__

#include <Renderable.hpp>

class DisplayFastLine: public Renderable {
    public:
        DisplayFastLine(unsigned short int positionX);
        void render(Display &display, unsigned short int current_menu_position);
    private:
        unsigned short int position_X;        
};

#endif // __DISPLAYFASTLINE_H__