#ifndef __TAMA_H__
#define __TAMA_H__

#include <Renderable.hpp>
#include <Display.hpp>
#include <Vector2.hpp>

class Tama: public Renderable {
    public:
        Tama();
        void render(Display &display, unsigned short int current_menu_position);
    private:
};

#endif // __TAMA_H__