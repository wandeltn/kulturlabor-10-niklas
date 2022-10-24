#include <StatsDisplay.hpp>

StatsDisplay::StatsDisplay(short int* value, unsigned short int positionX, unsigned short int positionY)
{
    #ifdef DEBUG
    Serial.println("inside StatsDisplay constructor");
    #endif
    use_alt_display = 0;
    display_value = value;
    position_X = positionX;
    position_Y = positionY;
}

StatsDisplay::StatsDisplay(bool* value, unsigned short int positionX, unsigned short int positionY)
{
    #ifdef DEBUG
    Serial.println("inside StatsDisplay bool constructor");
    #endif
    use_alt_display = 1;
    display_value_bool = value;
    position_X = positionX;
    position_Y = positionY;
}

void StatsDisplay::render(Display &display, unsigned short int current_menu_position)
{
    switch (use_alt_display)
    {
    case 0:
        display.setCursor(position_X, position_Y);
        display.print(*display_value);
        break;
    case 1:
        display.setCursor(position_X, position_Y);
        if (*display_value_bool) {
            display.print("ON");
        } else {
            display.print("OFF");
        }
    default:
        break;
    }

}
