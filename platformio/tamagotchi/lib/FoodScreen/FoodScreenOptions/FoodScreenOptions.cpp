#include <FoodScreenOptions/FoodScreenOptions.hpp>

FoodScreenOptions::FoodScreenOptions() {
    
}

void FoodScreenOptions::render(Display& display, unsigned short int current_menu_position)
{
    const char* display_options[8] = {
        "Burger",
        "Pasta",
        "Muffin",
        "Broccoli",
        "Salad",
        "Sushi",
        "Crepes",
        "Exit"
    };
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setCursor(10,0);             // Start at top-left corner

    for (unsigned short int option_index = 0; option_index < (sizeof(display_options) / sizeof(display_options[0])); option_index++) {
        display.setCursor(10, option_index * 8);
        display.print(display_options[option_index]);
    }
    Serial.println("inside render FoodScreenOptions");
    Serial.println("Finished FoodScreenOptions render");
}