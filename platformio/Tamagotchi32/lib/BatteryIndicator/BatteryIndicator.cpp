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
    ProgressBar BatteryBar = ProgressBar{(unsigned short)(position_X + 1), position_Y, 6, 3, (short int)(round(getChargePercent() / 25))};
    // ProgressBar BatteryBar = ProgressBar{(unsigned short)(position_X + 1), position_Y, 6, 3, 0};
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

inline double BatteryIndicator::getChargePercent()
{
    double x = ums3.getBatteryVoltage();
    double terms[] = {
        -5.3778504881236877e+003,
        5.2124642588825973e+003,
        -1.6742276657580881e+003,
        1.7987892384847973e+002
    };
  
    double t = 1;
    double r = 0;
    for (double c : terms) {
        r += c * t;
        t *= x;
    }
    return r;
}
