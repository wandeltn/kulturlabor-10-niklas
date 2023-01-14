#include "SubScreenOptions/SubScreenOptions.hpp"
#include <new>
#include <string>

SubScreenOptions::SubScreenOptions(const char* options_list[], unsigned char length)
{
    #ifdef DEBUG
    Serial.println("inside SubScreenOptions constructor");
    #endif
    options_list_ = options_list;
    list_length = length;
}

void SubScreenOptions::render(Display& display, unsigned short int current_menu_position)
{
    #ifdef DEBUG
    Serial.println("inside render SubScreenOptions");
    #endif
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setCursor(30,0);             // Start at top-left corner

    for (unsigned char option_index = 0; option_index < list_length; option_index++) {
        display.setCursor(30, option_index * 8);
        if (option_index == current_menu_position) {
            std::string selected_item{options_list_[option_index]};
            selected_item[0] = '>';
            display.print(selected_item.c_str());
        } else {
            display.print(options_list_[option_index]);
        }
    }
    #ifdef DEBUG
    Serial.println("exiting render SubScreenOptions");
    #endif
}

void SubScreenOptions::selectCurrentOption(unsigned short int current_menu_position)
{
    
}

