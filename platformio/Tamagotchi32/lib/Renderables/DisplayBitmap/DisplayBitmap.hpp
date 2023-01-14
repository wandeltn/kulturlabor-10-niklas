#ifndef __DISPLAYBITMAP_H__
#define __DISPLAYBITMAP_H__

#include <Renderable.hpp>
#include <ImageFormat.hpp>

class DisplayBitmap: public Renderable {
    public:
        DisplayBitmap(const ImageFormat* image, unsigned short int positionX, unsigned short int positionY);
        void render(Display &display, unsigned short int current_menu_position);
    private:
        const ImageFormat* display_bitmap;
        unsigned short int position_X, position_Y;
};

#endif // __DISPLAYBITMAP_H__