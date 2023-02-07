#include <PlayTama/PlaySoccer/PlaySoccer.hpp>
#include <Bitmaps.hpp>
#include <DisplayBitmap/DisplayBitmap.hpp>
#include <../DrawLine/DrawLine.hpp>
#include <PlayScreen.hpp>
#include <ScreenMessage.hpp>

extern bool schedule_rerender;
extern BaseScreen* active_screen;

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
    if (call_time <= millis()) {
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
                if (current_line_position >= 59) {
                    moving_down = !moving_down;
                }
            }
        }

        render_list.push_back(new DrawLine{
            10,
            32,
            118,
            current_line_position
        });

        schedule_rerender = true;
        call_time = millis() + 5;
    }
}

void PlaySoccer::onButtonBPressed()
{
    delete active_screen;
    if (current_line_position >= 27 && current_line_position <= 37) {
        active_screen = new ScreenMessage{
            "HIT",
            new PlayScreen()
        };
    } else {
        active_screen = new ScreenMessage{
            "MISS",
            new PlayScreen()
        };
    }
}

void PlaySoccer::onButtonDPressed()
{
    delete active_screen;
    active_screen = new PlayScreen();
}
