#include <PlayTama/PlayBadminton/PlayBadminton.hpp>
#include <Bitmaps.hpp>
#include <DisplayBitmap/DisplayBitmap.hpp>
#include <../DrawCircle/DrawCircle.hpp>
#include <MainScreen.hpp>

#define BALL_START_X    86
#define BALL_START_Y    32

extern BaseScreen* active_screen;

PlayBadminton::PlayBadminton(): BaseScreen(0)
{
    current_player_position = {42, 32};
    current_ball_position = {BALL_START_X, BALL_START_Y};
    ball_destination.x = random(5, 40);
    ball_destination.x = random(5, 59);

    render_list.push_back(new DisplayBitmap{
        &Bitmaps::Animations::PlayScreen::badminton_field_image,
        0,
        0
    });
    render_list.push_back(new DrawCircle{
        current_player_position,
        3
    });
    render_list.push_back(new DrawCircle{
        current_ball_position,
        2
    });
}

void PlayBadminton::updateScreen()
{
    for (Renderable* list_item : render_list) {
        delete list_item;
        list_item = nullptr;
    }
    render_list.clear();
    render_list.push_back(new DisplayBitmap{
        &Bitmaps::Animations::PlayScreen::badminton_field_image,
        0,
        0
    });
    render_list.push_back(new DrawCircle{
        current_player_position,
        3
    });

    // current_ball_position.x += (current_ball_position.x - ball_destination.x) / 5;
    // current_ball_position.y += (current_ball_position.y - ball_destination.y) / 5;
    // current_ball_position.x -= 1;
    // current_ball_position.y += (current_ball_position.y - ball_destination.y) / 5;

    if (
        current_ball_position.x + 5 >= current_player_position.x &&
        current_ball_position.x - 5 <= current_player_position.x &&
        current_ball_position.y + 5 >= current_player_position.y &&
        current_ball_position.y - 5 <= current_player_position.y
    ) {
        delete active_screen;
        active_screen = new MainScreen();
    } else if (
        current_ball_position.x + 5 >= ball_destination.x &&
        current_ball_position.x - 5 <= ball_destination.x &&
        current_ball_position.y + 5 >= ball_destination.y &&
        current_ball_position.y - 5 <= ball_destination.y
    ) {
        delete active_screen;
        active_screen = new MainScreen();
    }

    render_list.push_back(new DrawCircle{
        current_ball_position,
        2
    });
}

void PlayBadminton::onButtonAPressed()
{
    current_player_position.x -= 5;
}

void PlayBadminton::onButtonBPressed()
{
    current_player_position.y += 5;
}

void PlayBadminton::onButtonCPressed()
{
    current_player_position.x += 5;
}

void PlayBadminton::onButtonDPressed()
{
    current_player_position.y -= 5;
}
