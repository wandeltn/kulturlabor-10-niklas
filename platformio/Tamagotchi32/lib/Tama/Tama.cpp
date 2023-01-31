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
    if (tamaStatus.sleeping) {
        display.setCursor(tamaStatus.position.x + 50, tamaStatus.position.y - 2);
        display.print('Z');
        display.setCursor(tamaStatus.position.x + 55, tamaStatus.position.y - 7);
        display.print('Z');
        display.setCursor(tamaStatus.position.x + 60, tamaStatus.position.y - 12);
        display.print('Z');
    }
}