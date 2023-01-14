#ifndef __SUBSCREENOPTIONS_H__
#define __SUBSCREENOPTIONS_H__

#include <Renderable.hpp>

class SubScreenOptions: public Renderable {
    public: 
        SubScreenOptions(const char* options_list[], unsigned char length);
        void render(Display& display, unsigned short int current_menu_position);
        void selectCurrentOption(unsigned short int current_menu_position);
    private:
        unsigned char list_length;
        const char** options_list_;
};

#endif // __SUBSCREENOPTIONS_H__