#pragma once

#ifndef Renderable_H
#define Renderable_H

#include <Display.hpp>

class Renderable {
public:    
    virtual void selectCurrentOption(unsigned short int current_menu_position);
    virtual void render(Display &display, unsigned short int current_menu_position);     
private:
    
};

#endif