#pragma once

#ifndef MainMenuIcons_H
#define MainMenuIcons_H

#include <Renderable.hpp>

class MainMenuIcons: public Renderable {
    void render(Display &display, unsigned short int current_menu_position);   
};

#endif