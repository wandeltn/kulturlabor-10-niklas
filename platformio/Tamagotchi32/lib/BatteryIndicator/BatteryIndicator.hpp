#ifndef __BATTERYINDICATOR_H__
#define __BATTERYINDICATOR_H__

#include <Renderable.hpp>

class BatteryIndicator: public Renderable {
    public:
        BatteryIndicator(short int positionX, short int positionY);
        void render(Display &display, unsigned short int current_menu_position);
    private:
        inline float getChargePercent();
        unsigned short int position_X;
        unsigned short int position_Y;
        static inline float charge_level;
};

#endif // __BATTERYINDICATOR_H__