#ifndef BitmapMainMenu_H
#define BitmapMainMenu_H

#include <SPI.h>

class BitmapMainMenu {
    public:
		static const unsigned char PROGMEM food_menu_icon[32];
		static const unsigned char PROGMEM light_menu_icon[32];
		static const unsigned char PROGMEM play_menu_icon[32];
        static const unsigned char PROGMEM medicine_menu_icon[32];
		static const unsigned char PROGMEM poop_menu_icon[32];
		static const unsigned char PROGMEM stats_menu_icon[32];
		static const unsigned char PROGMEM dicipline_menu_icon[32];
		static const unsigned char PROGMEM attention_menu_icon[32];

};

#endif