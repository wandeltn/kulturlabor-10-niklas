#include <Tama.hpp>
#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <Bitmaps.hpp>

extern TamaStatus tamaStatus;
extern Timer timer;
extern bool screen_on;

Tama::Tama()
{
    updateMovement();
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

void Tama::updateMovement()
{
    int movementX = 0;
    if (position_X <= 20) {
        movementX = random(5);
    } else if (position_X >= 62) {
        movementX = random(-5, 0);
    } else {
        movementX = random(-5, 5);
    }

    position_X += movementX;

    if (screen_on) {
        timer.attach(new Timeable{
            .call_time = millis() + 1500,
            .linked_value = &position_X,
            .payload = 0,
            .notifier = &updateMovement
    });

    }

}

short int Tama::position_X = 0;
short int Tama::position_Y = 16;