#include <SystemStatsScreen.hpp>
#include "DisplayBitmap/DisplayBitmap.hpp"
#include <UMS3.h>
#include <BatteryIndicator.hpp>
#include <DisplayText.hpp>

extern BaseScreen* active_screen;
extern UMS3 ums3;

SystemStatsScreen::SystemStatsScreen(): BaseScreen(1) {
    render_list.push_back(new BatteryIndicator{97, 0});
    render_list.push_back(new DisplayText{50, 50, std::to_string(ums3.getBatteryVoltage())});
}

