#ifndef __DRAWLINE_H__
#define __DRAWLINE_H__

#include <Renderable.hpp>

class DrawLine: public Renderable {
    public:
        DrawLine(
            uint8_t postionX1,
            uint8_t postionY1,
            uint8_t postionX2,
            uint8_t postionY2
        );
        void render(Display &display, unsigned short current_menu_position);

    private:
        uint8_t positionX1_;
        uint8_t positionY1_;
        uint8_t positionX2_;
        uint8_t positionY2_;
};

#endif // __DRAWLINE_H__