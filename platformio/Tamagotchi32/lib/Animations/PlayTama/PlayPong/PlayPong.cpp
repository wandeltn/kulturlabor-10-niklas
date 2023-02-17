#include <PlayTama/PlayPong/PlayPong.hpp>
#include <../DrawLine/DrawLine.hpp>
#include <PlayScreen.hpp>
#include <DrawPixel.hpp>

extern bool schedule_rerender;
extern BaseScreen* active_screen;

PlayPong::PlayPong(): BaseScreen(0) {
    current_player_position = 30;
    current_bot_position = 30;
    current_ball_position = {64, 32};

    render_list.push_back(new DrawLine{
        3,
        current_player_position,
        3,
        current_player_position + 4
    });
    render_list.push_back(new DrawLine{
        125,
        current_bot_position,
        125,
        current_bot_position + 4
    });
    render_list.push_back(new DrawPixel{current_ball_position});
}