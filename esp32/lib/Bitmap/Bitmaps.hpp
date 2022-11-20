#pragma once

#ifndef Bitmaps_H
#define Bitmaps_H

#include <SPI.h>
#include <ImageFormat.hpp>

namespace Bitmaps {
	inline constexpr unsigned char food_menu_icon[32] PROGMEM = {
		// 'food_main_menu, 16x16px
		0xff, 0xff, 0x80, 0x01, 0xaa, 0x61, 0xaa, 0x61, 0xaa, 0x71, 0xbe, 0x71, 0x9c, 0x71, 0x9c, 0x79, 
		0x9c, 0x79, 0x9c, 0x71, 0x9c, 0x41, 0x9c, 0x41, 0x9c, 0x41, 0x80, 0x01, 0x80, 0x01, 0xff, 0xff, 
	};
	
	inline constexpr ImageFormat food_menu_icon_image {
        width: 16,
        height: 16,
        data: food_menu_icon
    };

	inline constexpr unsigned char light_menu_icon[32] PROGMEM = {
		// 'light_main_menu, 16x16px
		0xff, 0xff, 0xa0, 0x05, 0x93, 0xc9, 0x84, 0x21, 0xa8, 0x15, 0x89, 0x91, 0x8a, 0x51, 0xa9, 0x95, 
		0x8d, 0xb1, 0x87, 0xe1, 0x90, 0x09, 0xa3, 0xc5, 0x80, 0x01, 0x83, 0xc1, 0x80, 0x01, 0xff, 0xff
	};

	inline constexpr ImageFormat light_menu_icon_image {
        width: 16,
        height: 16,
        data: light_menu_icon
    };

	inline constexpr unsigned char play_menu_icon[32] PROGMEM = {
			// 'play_main_menu, 16x16px
		0xff, 0xff, 0x80, 0x01, 0x8c, 0x01, 0x9e, 0x01, 0x9e, 0x1d, 0x8c, 0x3d, 0x80, 0x7d, 0x80, 0xf9, 
		0x81, 0xf1, 0x83, 0xe1, 0x83, 0xc1, 0x8f, 0x81, 0x8e, 0x01, 0x86, 0x01, 0x80, 0x01, 0xff, 0xff, 
	};

	inline constexpr ImageFormat play_menu_icon_image {
        width: 16,
        height: 16,
        data: light_menu_icon
    };

	inline constexpr unsigned char medicine_menu_icon[32] PROGMEM = {
		// 'medicine_main_menu, 16x16px
		0xff, 0xff, 0x80, 0x01, 0x80, 0xa1, 0x80, 0x51, 0x80, 0x69, 0x80, 0xb5, 0x81, 0x19, 0x82, 0x25, 
		0x87, 0x41, 0x87, 0x81, 0x87, 0x01, 0x88, 0x01, 0x90, 0x01, 0x80, 0x01, 0x80, 0x01, 0xff, 0xff, 
	};

	inline constexpr ImageFormat medicine_menu_icon_image {
        width: 16,
        height: 16,
        data: medicine_menu_icon
    };

	inline constexpr unsigned char poop_menu_icon[32] PROGMEM = {
		// 'poop_main_menu, 16x16px
		0xff, 0xff, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x83, 0x01, 0x8c, 0x81, 0x9c, 0x81, 
		0x84, 0xe5, 0x8c, 0x1d, 0x98, 0x05, 0x98, 0x0d, 0x8f, 0xf9, 0x80, 0x01, 0x80, 0x01, 0xff, 0xff, 	
	};

	inline constexpr ImageFormat poop_menu_icon_image {
        width: 16,
        height: 16,
        data: poop_menu_icon
    };

	inline constexpr unsigned char stats_menu_icon[32] PROGMEM = {
		// 'stats_main_menu, 16x16px
		0xff, 0xff, 0x80, 0x01, 0x80, 0x01, 0x87, 0xe1, 0x9c, 0x39, 0xa2, 0x45, 0xa8, 0x15, 0xa0, 0x05, 
		0xa6, 0x05, 0xa7, 0x05, 0x93, 0x89, 0x91, 0x89, 0x90, 0x09, 0x8f, 0xf1, 0x80, 0x01, 0xff, 0xff, 
	};

	inline constexpr ImageFormat stats_menu_icon_image {
        width: 16,
        height: 16,
        data: stats_menu_icon
    };

	inline constexpr unsigned char dicipline_menu_icon[32] PROGMEM = {
		// 'dicipline_main_menu, 16x16px
		0xff, 0xff, 0x80, 0x01, 0x80, 0x09, 0x87, 0x85, 0x9c, 0xd1, 0x90, 0x49, 0xb0, 0x85, 0xa1, 0x15, 
		0xa2, 0x05, 0xb1, 0xe1, 0x90, 0x21, 0x9c, 0xe1, 0x87, 0x81, 0x80, 0x01, 0x80, 0x01, 0xff, 0xff, 
	};

	inline constexpr ImageFormat dicipline_menu_icon_image {
        width: 16,
        height: 16,
        data: dicipline_menu_icon
    };

	inline constexpr unsigned char attention_menu_icon[32] PROGMEM = {
		// 'attention_main_menu, 16x16px
		0xff, 0xff, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x88, 0x01, 0x81, 0x01, 0xa0, 0x39, 0xa0, 0x0d, 
		0x90, 0x05, 0x8e, 0x05, 0x80, 0x41, 0x80, 0x01, 0x80, 0x11, 0x80, 0x01, 0x80, 0x01, 0xff, 0xff, 
	};

	inline const unsigned char* options_list[8] = {
		food_menu_icon,
		light_menu_icon,
		play_menu_icon,
		medicine_menu_icon,
		poop_menu_icon,
		stats_menu_icon,
		dicipline_menu_icon,
		attention_menu_icon
	};

	inline constexpr unsigned char poop_icon [6] PROGMEM = {
	// 'poopicon, 6x6px
	0x48, 0x90, 0x48, 0x30, 0x78, 0xfc
	};

	inline constexpr ImageFormat poop_icon_image {
        width: 6,
        height: 6,
        data: poop_icon
    };

	inline constexpr unsigned char stone_icon [6] PROGMEM = {
	// 'stone, 6x6px
	0x78, 0xfc, 0xfc, 0xfc, 0x78, 0x00
	};

	inline constexpr ImageFormat stone_icon_image {
        width: 6,
        height: 6,
        data: stone_icon
    };

	namespace Tama
	{
		namespace EggStage
		{
			inline constexpr unsigned char  egg_up [288] PROGMEM = {
				// 'egg_up', 48x48px
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x00, 0x00, 
				0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0x00, 
				0x00, 0x03, 0xc7, 0xc1, 0xf0, 0x00, 0x00, 0x07, 0xc7, 0x80, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0x01, 
				0xf8, 0x00, 0x00, 0x3f, 0xfe, 0x0f, 0xfe, 0x00, 0x00, 0x3c, 0x7c, 0x0f, 0x9e, 0x00, 0x00, 0x3c, 
				0x78, 0x0f, 0x9e, 0x00, 0x00, 0x3c, 0x30, 0x03, 0xfe, 0x00, 0x00, 0x3c, 0x00, 0x01, 0xfe, 0x00, 
				0x00, 0x3c, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x78, 0x00, 0x00, 0xff, 0x00, 0x01, 0xf0, 0x00, 0x70, 
				0x07, 0xc0, 0x01, 0xe0, 0x00, 0xf0, 0x03, 0xe0, 0x01, 0xc0, 0x00, 0xf8, 0x01, 0xe0, 0x01, 0xc0, 
				0x03, 0xff, 0x01, 0xe0, 0x01, 0xc0, 0x07, 0xff, 0x01, 0xe0, 0x01, 0xe0, 0x07, 0x8f, 0x01, 0xe0, 
				0x01, 0xe0, 0x07, 0xcf, 0x03, 0xe0, 0x01, 0xf8, 0x01, 0xfe, 0x03, 0xe0, 0x01, 0xfc, 0x00, 0xf8, 
				0x03, 0xe0, 0x01, 0xfc, 0x00, 0xf8, 0x03, 0xe0, 0x01, 0xff, 0x80, 0x70, 0x03, 0xe0, 0x01, 0xe7, 
				0x80, 0x00, 0x03, 0xe0, 0x01, 0xc7, 0x80, 0x00, 0x03, 0xe0, 0x01, 0xe7, 0x80, 0x00, 0x03, 0xe0, 
				0x01, 0xff, 0x80, 0x06, 0x07, 0xc0, 0x00, 0x3e, 0x00, 0x0f, 0x0e, 0x00, 0x00, 0x3e, 0x00, 0x0f, 
				0x1e, 0x00, 0x00, 0x3e, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x1f, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x07, 
				0x80, 0xf8, 0xf0, 0x00, 0x00, 0x03, 0x80, 0xf9, 0xf0, 0x00, 0x00, 0x03, 0xf9, 0xff, 0xe0, 0x00, 
				0x00, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};

            inline constexpr ImageFormat egg_up_image {
                width: 48,
                height: 48,
                data: egg_up
            };

			inline const unsigned char  egg_side [288] PROGMEM = {
				// 'egg_side', 48x48px
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 
				0xff, 0xff, 0xf8, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 
				0x01, 0xf1, 0xf0, 0x00, 0x0f, 0x80, 0x01, 0xf1, 0xf0, 0x00, 0x07, 0x80, 0x03, 0xe1, 0xf0, 0x00, 
				0x07, 0x80, 0x0f, 0xdf, 0xc0, 0x00, 0x3f, 0xf0, 0x1f, 0x1f, 0x80, 0x00, 0x78, 0xf8, 0x1e, 0x1f, 
				0x00, 0x00, 0x78, 0xf8, 0x1e, 0x1f, 0x00, 0x00, 0x78, 0x7c, 0x3e, 0x0e, 0x00, 0x00, 0x78, 0x7c, 
				0xf0, 0x00, 0x00, 0xf8, 0x0f, 0x87, 0xe0, 0x00, 0x00, 0xf8, 0x0f, 0x87, 0xe0, 0x00, 0x00, 0xf8, 
				0x07, 0x87, 0xf0, 0x00, 0x00, 0xfc, 0x07, 0x07, 0xfc, 0x00, 0x0f, 0x0f, 0x00, 0x07, 0xfe, 0x00, 
				0x1f, 0x07, 0x80, 0x07, 0xfe, 0x00, 0x1f, 0x07, 0x80, 0x07, 0xff, 0x00, 0x0f, 0x87, 0x80, 0x07, 
				0xff, 0xe0, 0x07, 0xf0, 0x00, 0x07, 0xe1, 0xf0, 0x00, 0xf8, 0x00, 0x07, 0xe1, 0xf0, 0x00, 0xf8, 
				0x00, 0x07, 0xe1, 0xe0, 0x00, 0xf8, 0x00, 0x07, 0xff, 0xe0, 0x00, 0x20, 0x00, 0x1f, 0x3e, 0x00, 
				0x00, 0x00, 0x70, 0x7c, 0x1e, 0x00, 0x00, 0x00, 0x78, 0x78, 0x1e, 0x00, 0x00, 0x00, 0xf8, 0x78, 
				0x0f, 0x80, 0x00, 0x01, 0xff, 0xf8, 0x03, 0xe0, 0x00, 0x07, 0x87, 0xc0, 0x03, 0xf0, 0x00, 0x07, 
				0x87, 0x80, 0x01, 0xf0, 0x00, 0x07, 0x87, 0x80, 0x01, 0xf8, 0x00, 0x0f, 0xcf, 0x80, 0x00, 0x3f, 
				0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 
				0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};

			inline constexpr ImageFormat egg_side_image {
				width: 48,
				height: 48,
				data: egg_side
			};

			inline const ImageFormat options_list[2] = {
				egg_up_image,
				egg_side_image
			};
		} // namespace EggStage
		
		namespace BabyStage
		{
			inline constexpr unsigned char  shiropetitchi [288] PROGMEM = {
				// 'shiropetitchi', 48x48px
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 
				0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 
				0x00, 0x00, 0x00, 0x1f, 0xf8, 0x07, 0xfe, 0x00, 0x00, 0x3f, 0xf8, 0x03, 0xff, 0x00, 0x00, 0x3f, 
				0xf0, 0x03, 0xff, 0x00, 0x00, 0x3f, 0xf0, 0x03, 0xff, 0x00, 0x00, 0x7f, 0xe0, 0x01, 0xff, 0x80, 
				0x03, 0xf0, 0x00, 0x00, 0x01, 0xf0, 0x03, 0xe0, 0x00, 0x00, 0x01, 0xf0, 0x03, 0xe0, 0x00, 0x00, 
				0x00, 0xf0, 0x03, 0xe0, 0x00, 0x00, 0x00, 0xf0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0x03, 0xc1, 
				0xf0, 0x03, 0xe0, 0xf0, 0x03, 0xc1, 0xf0, 0x03, 0xe0, 0xf0, 0x03, 0xc1, 0xf0, 0x03, 0xe0, 0xf0, 
				0x03, 0xc1, 0xf0, 0x03, 0xe0, 0xf0, 0x03, 0xe0, 0x60, 0x00, 0x80, 0xf0, 0x03, 0xe0, 0x00, 0x00, 
				0x00, 0xf0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0x03, 0xe0, 
				0x00, 0x00, 0x00, 0xf0, 0x03, 0xc0, 0x03, 0xf8, 0x00, 0xf0, 0x03, 0xc0, 0x07, 0xfc, 0x00, 0xf0, 
				0x03, 0xc0, 0x0f, 0xfc, 0x00, 0xf0, 0x03, 0xc0, 0x0f, 0xfc, 0x00, 0xf0, 0x03, 0xe0, 0x1f, 0xfe, 
				0x01, 0xf0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 
				0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 
				0x03, 0xf0, 0x00, 0x00, 0x01, 0xf0, 0x03, 0xe0, 0x00, 0x00, 0x01, 0xf0, 0x03, 0xc0, 0x00, 0x00, 
				0x00, 0xf0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};

			inline constexpr ImageFormat shiropetitchi_image = {
				width: 48,
				height: 48,
				data: shiropetitchi
			};

			inline constexpr unsigned char  petitchi [288] PROGMEM = {
				// 'petitchi', 48x48px
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 
				0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 
				0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 
				0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xff, 
				0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf8, 
				0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 
				0xff, 0xf8, 0x3f, 0xf8, 0x7f, 0xff, 0xe1, 0xf8, 0x3f, 0xf0, 0x3f, 0xff, 0xc1, 0xf8, 0x3f, 0xf0, 
				0x3f, 0xff, 0xc1, 0xf8, 0x3f, 0xf0, 0x3f, 0xff, 0xc1, 0xf8, 0x3f, 0xf8, 0x7f, 0xff, 0xe1, 0xf8, 
				0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 
				0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xff, 
				0xff, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xc0, 0x0f, 0xff, 0xf8, 0x3f, 0xff, 0xc0, 0x07, 0xff, 0xf8, 
				0x7f, 0xff, 0xc0, 0x07, 0xff, 0xf8, 0x7f, 0xff, 0xc0, 0x0f, 0xff, 0xf8, 0x3f, 0xff, 0xe0, 0x0f, 
				0xff, 0xf8, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 
				0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 
				0x00, 0x1f, 0xe0, 0x00, 0x7f, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0x00, 0x00, 0x0f, 0xc0, 0x00, 
				0x3f, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};

			inline constexpr ImageFormat petitchi_image = {
				width: 48,
				height: 48,
				data: petitchi
			};

			inline constexpr ImageFormat options_list[2] = {
				shiropetitchi_image,
				petitchi_image
			};
		} // namespace BabyStage
		
		namespace TeenStage
		{
			inline constexpr unsigned char  hinotamatchi [288] PROGMEM = {
				// 'hinotamatchi', 48x48px
				0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x03, 0x80, 0xf0, 0x1c, 0x00, 0x00, 0x03, 
				0x80, 0xf0, 0x1c, 0x00, 0x00, 0x03, 0x80, 0xf0, 0x1c, 0x00, 0x00, 0x03, 0x87, 0x9c, 0x1c, 0x00, 
				0x00, 0x03, 0x87, 0x0e, 0x1e, 0x00, 0x00, 0x03, 0x8f, 0x0f, 0x1e, 0x00, 0x00, 0x07, 0x9f, 0x0f, 
				0x9f, 0x00, 0x00, 0x3c, 0x7c, 0x03, 0xe7, 0x80, 0x00, 0x3c, 0x78, 0x01, 0xe3, 0xc0, 0x00, 0x3c, 
				0x78, 0x01, 0xe3, 0xc0, 0x00, 0x3c, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x3c, 0x00, 0x00, 0x03, 0xc0, 
				0x00, 0x3c, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x3c, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x3c, 0x78, 0x00, 
				0x00, 0x7c, 0x00, 0x3c, 0x78, 0x00, 0x00, 0x7c, 0x00, 0x3c, 0x78, 0x00, 0x00, 0x3c, 0x00, 0xfc, 
				0x00, 0x00, 0x00, 0x3c, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x3c, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x3c, 
				0x03, 0xf8, 0x00, 0x00, 0x00, 0x3c, 0x1e, 0x00, 0x00, 0x01, 0xe0, 0x3c, 0x1e, 0x00, 0x00, 0x01, 
				0xe0, 0x3c, 0x1e, 0x00, 0x00, 0x01, 0xe0, 0x7c, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x3c, 0x1f, 0xfc, 
                0x00, 0x00, 0x00, 0x7c, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x7c, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x7c, 
				0x1e, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x1e, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x1e, 0x00, 0x00, 0x00, 
				0x03, 0x80, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x1e, 0x00, 0x01, 0xfc, 
				0x00, 0x00, 0x1c, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x00, 
				0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xff, 
				0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};

			inline constexpr ImageFormat hinotamatchi_image = {
				width: 48,
				height: 48,
				data: hinotamatchi
			};

			inline constexpr unsigned char  hinagotchi [288] PROGMEM = {
				// 'hinagotchi', 48x48px
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 
				0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 
				0xc0, 0x00, 0x00, 0x07, 0x03, 0xfc, 0xf0, 0x00, 0x00, 0x07, 0x01, 0xf8, 0x70, 0x00, 0x00, 0x0f, 
				0x01, 0xf8, 0x78, 0x00, 0x00, 0x3c, 0xe0, 0x00, 0x3c, 0x00, 0x00, 0x78, 0xf0, 0x00, 0x1e, 0x00, 
				0x00, 0x78, 0xf0, 0x00, 0x0e, 0x00, 0x00, 0xfd, 0xe0, 0x00, 0x0e, 0x00, 0x03, 0xff, 0x00, 0x38, 
				0x0e, 0x00, 0x03, 0xff, 0x00, 0x38, 0x0e, 0x00, 0x03, 0xff, 0x00, 0x38, 0x0e, 0x00, 0x1e, 0x01, 
				0xe0, 0x00, 0x0e, 0x00, 0x3c, 0x00, 0xf0, 0x00, 0x0e, 0x00, 0x3c, 0x00, 0xe0, 0x00, 0x0e, 0x00, 
				0x03, 0xff, 0x80, 0x00, 0x0e, 0x00, 0x03, 0xff, 0x00, 0x00, 0x0e, 0x00, 0x03, 0xff, 0x00, 0x00, 
				0x0e, 0x00, 0x07, 0xff, 0x00, 0x00, 0x07, 0x00, 0x3c, 0x00, 0xe0, 0x00, 0x01, 0xe0, 0x3c, 0x00, 
				0xf0, 0x00, 0x01, 0xe0, 0x1e, 0x01, 0xe0, 0x00, 0x03, 0xe0, 0x07, 0xff, 0x00, 0x00, 0x7f, 0x00, 
				0x03, 0xff, 0x00, 0x00, 0x7e, 0x00, 0x03, 0xff, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x3f, 0x00, 0x00, 
				0x7c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x78, 0x00, 0x00, 0x07, 0x00, 0x00, 0x70, 0x00, 0x00, 0x07, 
				0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 
				0x00, 0x01, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xf0, 0x07, 0xf0, 0x00, 0x00, 0x07, 0xf0, 0x07, 
				0xf0, 0x00, 0x00, 0x07, 0xf0, 0x07, 0xf0, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xf0, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};

			inline constexpr ImageFormat hinagotchi_image = {
				width: 48,
				height: 48,
				data: hinagotchi
			};

			inline constexpr ImageFormat options_list[2] = {
				hinotamatchi_image,
				hinagotchi_image
			};
		} // namespace TeenStage
		
        namespace AdultStage
        {
            inline constexpr unsigned char  memetchi [288] PROGMEM = {
                // 'memetchi', 48x48px
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 
                0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 
                0x0e, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 
                0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
                0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x0f, 
                0xc0, 0x00, 0xfc, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x7c, 0x00, 0x00, 0x70, 0x00, 0x00, 0x47, 0x00, 
                0x00, 0x70, 0x00, 0x00, 0x07, 0x00, 0x01, 0xe0, 0xe0, 0x01, 0xe3, 0xc0, 0x01, 0xc1, 0xf0, 0x03, 
                0xe0, 0xc0, 0x01, 0x81, 0xf0, 0x03, 0xe0, 0xc0, 0x01, 0x81, 0xc0, 0x03, 0x80, 0xc0, 0x01, 0x81, 
                0xc0, 0x03, 0x80, 0xc0, 0x01, 0x81, 0xf0, 0x03, 0xe0, 0xc0, 0x01, 0x81, 0xf0, 0x03, 0xe0, 0xc0, 
                0x01, 0x81, 0xf0, 0x03, 0xe0, 0xc0, 0x01, 0x81, 0xf0, 0x01, 0xe0, 0xc0, 0x01, 0x80, 0x00, 0x00, 
                0x00, 0xc0, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x70, 0x3c, 0x1f, 0x83, 0x00, 0x00, 0x70, 
                0x7e, 0x1f, 0x87, 0x00, 0x00, 0x3e, 0x3f, 0xff, 0x1e, 0x00, 0x00, 0x0e, 0x03, 0xe0, 0x1c, 0x00, 
                0x00, 0x0f, 0x03, 0xe0, 0x18, 0x00, 0x00, 0x01, 0xf0, 0x03, 0xe0, 0x00, 0x00, 0x01, 0xf0, 0x03, 
                0xe0, 0x00, 0x00, 0x00, 0x70, 0x03, 0x80, 0x00, 0x00, 0x00, 0x70, 0x03, 0x80, 0x00, 0x00, 0x00, 
                0xff, 0xff, 0xe0, 0x00, 0x00, 0x01, 0xcf, 0xfe, 0x60, 0x00, 0x00, 0x01, 0xcf, 0xfe, 0x60, 0x00, 
                0x00, 0x01, 0xcf, 0xfe, 0x60, 0x00, 0x00, 0x00, 0x0e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1e, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            };

			inline constexpr ImageFormat memetchi_image = {
				width: 48,
				height: 48,
				data: memetchi
			};

            inline constexpr unsigned char  mimitchi [288] PROGMEM = {
                // 'mimitchi', 48x48px
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x07, 0xf0, 0x00, 
                0x00, 0x3f, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x3f, 0x80, 0x07, 0xf0, 0x00, 0x00, 0xff, 0xe0, 0x1f, 
                0xfc, 0x00, 0x00, 0xff, 0xe0, 0x1f, 0xfc, 0x00, 0x00, 0xff, 0xe0, 0x1f, 0xfc, 0x00, 0x00, 0xff, 
                0xe0, 0x1f, 0xfc, 0x00, 0x00, 0xff, 0xf0, 0x1f, 0xfc, 0x00, 0x00, 0x3f, 0xfc, 0xff, 0xf0, 0x00, 
                0x00, 0x3f, 0xfe, 0xff, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 
                0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x1e, 0x00, 0x40, 0xf0, 0x00, 0x00, 0x1c, 
                0x00, 0x00, 0xf0, 0x00, 0x00, 0x1c, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x67, 0x00, 0x03, 0xbc, 0x00, 
                0x00, 0xe3, 0x00, 0x07, 0x9c, 0x00, 0x00, 0xe2, 0x1f, 0xe3, 0x0c, 0x00, 0x00, 0xe0, 0x1f, 0xe0, 
                0x0c, 0x00, 0x00, 0xe0, 0x1f, 0xe0, 0x0c, 0x00, 0x03, 0xf8, 0x1f, 0xe0, 0x0f, 0x00, 0x07, 0xfc, 
                0x00, 0x00, 0x0f, 0x80, 0x07, 0xfc, 0x00, 0x00, 0x0f, 0x80, 0x07, 0xfc, 0x00, 0x00, 0x0f, 0x80, 
                0x07, 0xfc, 0x00, 0x00, 0x0f, 0x80, 0x07, 0xfc, 0x00, 0x00, 0x0f, 0x80, 0x00, 0xe0, 0x00, 0x00, 
                0x0c, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x60, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x3c, 
                0x00, 0x07, 0xf0, 0x00, 0x00, 0x1c, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x00, 
                0x00, 0x03, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 
                0xf0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            };

			inline constexpr ImageFormat mimitchi_image = {
				width: 48,
				height: 48,
				data: mimitchi
			};

			inline constexpr ImageFormat options_list[2] = {
				memetchi_image,
				mimitchi_image
			};
		} // namespace AdultStage
        
        namespace SeniorStage
        {
            inline constexpr unsigned char  otokitchi [288] PROGMEM = {
                // 'otokitchi', 48x48px
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xff, 0xff, 
                0xff, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xfe, 0x70, 0x00, 0x03, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x07, 
                0x03, 0x80, 0x0f, 0xf0, 0x00, 0x07, 0x03, 0x80, 0x0f, 0xf0, 0x00, 0x1f, 0xfe, 0xff, 0xfb, 0xc0, 
                0x00, 0x3f, 0xfe, 0x7f, 0xf9, 0xc0, 0x00, 0x3f, 0xfe, 0x7f, 0xf9, 0xc0, 0x00, 0x39, 0xce, 0x67, 
                0x39, 0xc0, 0x00, 0x3d, 0xde, 0x77, 0xb9, 0xc0, 0x00, 0x3f, 0xfe, 0x7f, 0xf9, 0xc0, 0x00, 0x3f, 
                0xfe, 0x7f, 0xf9, 0xc0, 0x00, 0xe1, 0xe3, 0xc0, 0x01, 0xc0, 0x00, 0xe1, 0xc3, 0x80, 0x01, 0xc0, 
                0x00, 0xe0, 0xc1, 0x80, 0xf1, 0xc0, 0x00, 0xe0, 0x00, 0x00, 0xf9, 0xc0, 0x00, 0xe0, 0x00, 0x00, 
                0xf9, 0x80, 0x00, 0x3f, 0xff, 0xfc, 0x0e, 0x00, 0x00, 0x1f, 0xff, 0xfc, 0x0e, 0x00, 0x00, 0x0f, 
                0xff, 0xf8, 0x1c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0x00, 0x07, 0x00, 0x00, 0x7c, 0x00, 
                0x00, 0x07, 0x30, 0x1c, 0xfe, 0x00, 0x00, 0x07, 0x78, 0x1c, 0xfe, 0x00, 0x00, 0xf9, 0xff, 0xff, 
                0x81, 0xc0, 0x00, 0xf9, 0xff, 0xff, 0x01, 0xc0, 0x03, 0xf1, 0xff, 0xff, 0x01, 0xc0, 0x03, 0x01, 
                0xc0, 0x60, 0x01, 0xc0, 0x03, 0x81, 0xc0, 0x60, 0x01, 0x80, 0x00, 0xe1, 0xc0, 0x60, 0x06, 0x00, 
                0x00, 0xe1, 0xc0, 0x60, 0x06, 0x00, 0x03, 0xe0, 0x71, 0xc0, 0x07, 0x80, 0x03, 0xe0, 0x33, 0x80, 
                0x07, 0xc0, 0x03, 0xc0, 0x31, 0x80, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            };

			inline constexpr ImageFormat otokitchi_image = {
				width: 48,
				height: 48,
				data: otokitchi
			};

            inline constexpr unsigned char  ojitchi [288] PROGMEM = {
                // 'ojitchi', 48x48px
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x1c, 0x00, 
                0x00, 0x00, 0x01, 0xc0, 0x1c, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x07, 0x38, 
                0x03, 0x00, 0x00, 0x00, 0x07, 0x70, 0x07, 0x80, 0x00, 0x00, 0x01, 0xc1, 0xff, 0xff, 0xe0, 0x00, 
                0x01, 0xc3, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0e, 0x00, 0x00, 
                0x1c, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x3b, 0x80, 0x0c, 0x07, 0x00, 0x00, 0x3b, 
                0xc0, 0x0e, 0x07, 0x00, 0x00, 0x3b, 0xe0, 0x0f, 0x9f, 0xc0, 0x00, 0x39, 0xf0, 0x0f, 0x9f, 0xe0, 
                0x00, 0xf9, 0xe0, 0x0f, 0x1f, 0xe0, 0x01, 0xf8, 0x00, 0x00, 0x1f, 0xe0, 0x01, 0xf8, 0x00, 0x00, 
                0x1f, 0xe0, 0x01, 0xf8, 0x73, 0x00, 0x07, 0xe0, 0x01, 0xf8, 0x73, 0x00, 0x07, 0xc0, 0x00, 0x78, 
                0x20, 0x0c, 0x07, 0x80, 0x00, 0x38, 0x00, 0x0e, 0x07, 0x00, 0x00, 0x38, 0x00, 0x0e, 0x07, 0x00, 
                0x00, 0x38, 0x00, 0x0e, 0x07, 0x00, 0x00, 0x38, 0x1c, 0x03, 0x87, 0x00, 0x00, 0x38, 0x1c, 0x03, 
                0x87, 0x00, 0x00, 0x38, 0x78, 0x00, 0xe7, 0x00, 0x00, 0x38, 0x70, 0x00, 0x67, 0x00, 0x00, 0x3c, 
                0x70, 0x00, 0xff, 0x00, 0x00, 0x3e, 0x70, 0x00, 0xff, 0x00, 0x00, 0x7e, 0x70, 0x00, 0xff, 0x80, 
                0x00, 0xee, 0x7f, 0xf3, 0xff, 0xc0, 0x01, 0xce, 0x7f, 0xf3, 0xdd, 0xe0, 0x01, 0xc7, 0xff, 0xf3, 
                0xf8, 0xe0, 0x01, 0xc1, 0xf0, 0x03, 0xe0, 0xe0, 0x00, 0xe1, 0xf8, 0x07, 0xe1, 0xc0, 0x00, 0x70, 
                0x1f, 0xfe, 0x07, 0x80, 0x00, 0x78, 0x1f, 0xfc, 0x07, 0x00, 0x00, 0xf8, 0x0f, 0xf8, 0x07, 0xc0, 
                0x01, 0xf8, 0x00, 0x00, 0x07, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            };

			inline constexpr ImageFormat ojitchi_image = {
				width: 48,
				height: 48,
				data: ojitchi
			};

			inline constexpr ImageFormat options_list[2] = {
				otokitchi_image,
				ojitchi_image
			};
		} // namespace SeniorStage
        
		inline const ImageFormat* evolution_list[5] = {
			EggStage::options_list,
			BabyStage::options_list,
			TeenStage::options_list,
			AdultStage::options_list,
			SeniorStage::options_list,
		};

		inline constexpr unsigned short int state_count[5] = {
			2,
			2,
			2,
			2,
			2
		};


	} // namespace Tama
	
};

#endif