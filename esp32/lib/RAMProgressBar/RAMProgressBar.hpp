#ifndef __RAMPROGRESSBAR_H__
#define __RAMPROGRESSBAR_H__

#include <Renderable.hpp>

class RAMProgressBar: public Renderable {
    public: 
        RAMProgressBar(
            unsigned short int x,
            unsigned short int y,
            unsigned short int w,
            unsigned short int h
        );
        void render(Display& display, unsigned short int current_menu_position);
    private:
        static unsigned short int positionX, positionY, width, height;
};

#endif // __RAMPROGRESSBAR_H__