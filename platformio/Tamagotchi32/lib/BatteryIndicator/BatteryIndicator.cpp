#include <BatteryIndicator.hpp>
#include <ProgressBar.hpp>
#include <Bitmaps.hpp>
#include <math.h>
#include <UMS3.h>

extern UMS3 ums3;

BatteryIndicator::BatteryIndicator(short int positionX, short int positionY) {
    position_X = positionX;
    position_Y = positionY;
    charge_level = ums3.getBatteryVoltage();
}

void BatteryIndicator::render(Display &display, unsigned short int current_menu_position) {
    // ProgressBar BatteryBar = ProgressBar{position_X + 1, position_Y, 6, 3, (short int)(round(getChargePercent() / 25))};
    ProgressBar BatteryBar = ProgressBar{(unsigned short)(position_X + 1), position_Y, 6, 3, 0};
    BatteryBar.render(display, current_menu_position);
    display.drawPixel(position_X, position_Y + 1, SSD1306_WHITE);
    if (ums3.getVbusPresent()) {
        display.drawBitmap(
            position_X -4,
            position_Y,
            Bitmaps::Battery::charging_icon_image.data,
            Bitmaps::Battery::charging_icon_image.width,
            Bitmaps::Battery::charging_icon_image.height,
            SSD1306_WHITE
        );
    }
    //draw battery voltage
    display.setCursor(position_X - 40, position_Y);
    display.write(std::to_string(ums3.getBatteryVoltage()).c_str());
}

inline float BatteryIndicator::getChargePercent()
{
    return 50.55;
}
