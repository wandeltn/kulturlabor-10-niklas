#ifndef __ICONSBAR_H__
#define __ICONSBAR_H__

#include <Renderable.hpp>
#include <ImageFormat.hpp>


class IconsBar: public Renderable {
    public:
        IconsBar(const ImageFormat* image, short int* amount, unsigned short int positionX);
        IconsBar(const ImageFormat* image, short int* amount, unsigned short int positionX, bool convert);
        void render(Display &display, unsigned short int current_menu_position);
    private:
        const ImageFormat* display_bitmap;
        unsigned short int position_X;
        short int* icon_amount; 
        bool convert_value;
};

#endif // __ICONSBAR_H__