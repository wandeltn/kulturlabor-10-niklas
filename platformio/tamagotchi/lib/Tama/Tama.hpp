#ifndef __TAMA_H__
#define __TAMA_H__

#include <Renderable.hpp>
#include <Display.hpp>

class Tama: public Renderable {
    public:
        Tama();
        void render(Display &display, unsigned short int current_menu_position);
        static void updateMovementX();
        static void updateMovementY();

        static short int position_X, position_Y;
    private:
};

#endif // __TAMA_H__