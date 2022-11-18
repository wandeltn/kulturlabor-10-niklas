#ifndef __STATSDISPLAY_H__
#define __STATSDISPLAY_H__

#include <Renderable.hpp>

class StatsDisplay: public Renderable {
    public:
        StatsDisplay(short int* value, unsigned short int positionX, unsigned short int positionY);
        StatsDisplay(bool* value, unsigned short int positionX, unsigned short int positionY);
        void render(Display &display, unsigned short int current_menu_position);
    private:
        const short int* display_value;
        const bool* display_value_bool;
        unsigned short int position_X, position_Y;
        short int use_alt_display;
};

#endif // __STATSDISPLAY_H__