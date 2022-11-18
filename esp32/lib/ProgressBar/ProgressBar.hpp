#ifndef __PROGRESSBAR_H__
#define __PROGRESSBAR_H__

#include <Renderable.hpp>

class ProgressBar: public Renderable {
    public: 
        ProgressBar(
            unsigned short int x,
            unsigned short int y,
            unsigned short int w,
            unsigned short int h,
            short int percent_fill_height
        );
        void render(Display& display, unsigned short int current_menu_position);
    private:
        unsigned short int positionX, positionY, width, height, display_fill_height;
};

#endif // __PROGRESSBAR_H__