#include "SubScreenOptions/SubScreenOptions.hpp"
#include <new>
#include <string>

SubScreenOptions::SubScreenOptions(const char* options_list[], unsigned char length)
{
    Serial.println("inside SubScreenOptions constructor");
    options_list_ = options_list;
    list_length = length;
}

void SubScreenOptions::render(Display& display, unsigned short int current_menu_position)
{
    Serial.println("inside render SubScreenOptions");
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setCursor(10,0);             // Start at top-left corner

    for (unsigned char option_index = 0; option_index < list_length; option_index++) {
        display.setCursor(10, option_index * 8);
        if (option_index == current_menu_position) {
            std::string selected_item{options_list_[option_index]};
            selected_item[0] = '>';
            display.print(selected_item.c_str());
        } else {
            display.print(options_list_[option_index]);
        }
    }
    Serial.println("exiting render SubScreenOptions");
}

void SubScreenOptions::selectCurrentOption(unsigned short int current_menu_position)
{
    
}

