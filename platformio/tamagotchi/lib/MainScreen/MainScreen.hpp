#include <Renderable.hpp>
#include <BaseScreen.hpp>

class MainScreen: Renderable, public BaseScreen {
    public:
        void render(Display &display, unsigned short int current_menu_position);
    private:

};