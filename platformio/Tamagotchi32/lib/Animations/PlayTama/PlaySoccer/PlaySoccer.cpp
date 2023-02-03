#include <PlayTama/PlaySoccer/PlaySoccer.hpp>
#include <Bitmaps.hpp>
#include <DisplayBitmap/DisplayBitmap.hpp>
#include <../DrawLine/DrawLine.hpp>

extern bool schedule_rerender;

PlaySoccer::PlaySoccer(): BaseScreen(0)
{
    current_line_position = 0;
    call_time = 0;

    render_list.push_back(new DisplayBitmap{
        &Bitmaps::Animations::PlayScreen::soccer_field_image,
        0,
        0
    });
    render_list.push_back(new DrawLine{
        10,
        32,
        118,
        current_line_position
    });
}

void PlaySoccer::updateScreen()
{
    for (Renderable* list_item : render_list) {
        delete list_item;
        list_item = nullptr;
    }
    render_list.clear();

    render_list.push_back(new DisplayBitmap{
        &Bitmaps::Animations::PlayScreen::soccer_field_image,
        0,
        0
    });

    if (call_time <= millis()) {
        call_time = millis() + 50;

        if (moving_down) {
            current_line_position--;
            if (current_line_position <= 5) {
                moving_down = !moving_down;
            }
        } else {
            current_line_position++;
            if (current_line_position >= 123) {
                moving_down = !moving_down;
            }
        }
    }
    schedule_rerender = true;
}
