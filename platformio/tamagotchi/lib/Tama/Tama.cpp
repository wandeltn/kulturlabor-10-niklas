#include <Tama.hpp>
#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <Bitmaps.hpp>

extern TamaStatus tamaStatus;
extern Timer timer;
extern bool screen_on;

Tama::Tama()
{
    #ifdef DEBUG
    Serial.pirntln("inside Tama constructor");
    #endif
}

void Tama::render(Display &display, unsigned short int current_menu_position)
{
    display.drawBitmap(
        tamaStatus.position.x,
        tamaStatus.position.y,
        tamaStatus.current_display_state.data,
        tamaStatus.current_display_state.width,
        tamaStatus.current_display_state.height,
        SSD1306_WHITE
    );
}