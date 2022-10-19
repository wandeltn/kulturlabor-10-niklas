#include <MainScreen.hpp>
#include "../Renderables/MainMenuIcons/MainMenuIcons.hpp"

MainScreen::MainScreen() {
    render_list.push_back(new MainMenuIcons());
}