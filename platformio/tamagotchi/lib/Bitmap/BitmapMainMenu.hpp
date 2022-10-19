#ifndef BitmapMainMenu_H
#define BitmapMainMenu_H

#include <SPI.h>

class BitmapMainMenu {
    public:
		static const unsigned char food_menu_icon[32];
		static const unsigned char light_menu_icon[32];
		static const unsigned char play_menu_icon[32];
        static const unsigned char medicine_menu_icon[32];
		static const unsigned char poop_menu_icon[32];
		static const unsigned char stats_menu_icon[32];
		static const unsigned char dicipline_menu_icon[32];
		static const unsigned char attention_menu_icon[32];

		static const unsigned char* options_list[8];

};

#endif