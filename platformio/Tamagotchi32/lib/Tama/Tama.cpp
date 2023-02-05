#include <Tama.hpp>
#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <Bitmaps.hpp>

extern TamaStatus tamaStatus;
extern Timer timer;
extern bool screen_on;
extern bool schedule_rerender;

Tama::Tama(): Renderable()
{
    #ifdef DEBUG
    Serial.pirntln("inside Tama constructor");
    #endif
    jump_time = 0;
}

void Tama::update()
{
    if (jump_time <= millis()) { 
        tamaStatus.updateJump();
        schedule_rerender = true;
        jump_time = millis() + 50;
    }
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
    }
}