#ifndef __DISPLAYTEXT_H__
#define __DISPLAYTEXT_H__

#include <string>
#include <Renderable.hpp>

class DisplayText: public Renderable {
    public:
        DisplayText(short int positionX, short int positionY, std::string text);
        void render(Display &display, unsigned short int current_menu_position);
    private:
        short int position_X, position_Y;
        std::string display_text;
};

#endif // __DISPLAYTEXT_H__