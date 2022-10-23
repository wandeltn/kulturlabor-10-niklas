#include <Tama.hpp>
#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <Bitmaps.hpp>

extern TamaStatus tamaStatus;
extern Timer timer;

Tama::Tama()
{
    updateMovementX();
    updateMovementY();
}

void Tama::render(Display &display, unsigned short int current_menu_position)
{
    display.drawBitmap(
        position_X,
        position_Y,
        tamaStatus.current_display_state.data,
        tamaStatus.current_display_state.width,
        tamaStatus.current_display_state.height,
        SSD1306_WHITE
    );
}

void Tama::updateMovementX()
{
    timer.attach(new Timeable{
        .call_time = millis() + 1500,
        .linked_value = &position_X,
        .payload = (short)random(-5, 5),
        .notifier = &updateMovementX
    });
}

void Tama::updateMovementY()
{
    timer.attach(new Timeable{
        .call_time = millis() + 1500,
        .linked_value = &position_Y,
        .payload = (short)random(-5, 5),
        .notifier = &updateMovementY
    });
}

short int Tama::position_X = 0;
short int Tama::position_Y = 0;