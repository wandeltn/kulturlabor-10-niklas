#ifndef BaseScreen_H
#define BaseScreen_H

class BaseScreen {
    public:
        virtual void render(Display &display, unsigned short int current_menu_position);
};

#endif