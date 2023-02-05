#ifndef __DRAWKEYBOARD_H__
#define __DRAWKEYBOARD_H__

#include <Renderable.hpp>

class DrawKeyboard : public Renderable {
    public: 
        DrawKeyboard();
        void render(Display &display, unsigned short current_menu_position);
    private: 
        std::string output_string_;
        BaseScreen* exit_screen_;
};

#endif // __DRAWKEYBOARD_H__