#ifndef __TAMA_H__
#define __TAMA_H__

#include <Renderable.hpp>
#include <Display.hpp>
#include <Vector2.hpp>

class Tama: public Renderable {
    public:
        Tama();
        void update();
        void render(Display &display, unsigned short int current_menu_position);
    private:
        unsigned long jump_time;
};

#endif // __TAMA_H__