#ifndef __DRAWCIRCLE_H__
#define __DRAWCIRCLE_H__

#include <Renderable.hpp>
#include <Vector2.hpp>

class DrawCircle: public Renderable {
    public:
        DrawCircle(uint8_t positionX, uint8_t positionY, uint8_t radius);
        DrawCircle(Vector2 position, uint8_t radius);
        void render(Display &display, unsigned short current_menu_position);

    private: 
        uint8_t positionX_;
        uint8_t positionY_;
        uint8_t radius_;
};

#endif // __DRAWCIRCLE_H__