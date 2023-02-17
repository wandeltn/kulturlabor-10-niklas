#ifndef __DRAWPIXEL_H__
#define __DRAWPIXEL_H__

#include <Renderable.hpp>

class DrawPixel: public Renderable {
    public:
        DrawPixel(short position_x, short position_y);
        DrawPixel(Vector2 position);
        void render(Display &display, unsigned short current_menu_position);
    private:
        short positionX, positionY;
};

#endif // __DRAWPIXEL_H__