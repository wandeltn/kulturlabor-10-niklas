#pragma once

#ifndef Renderable_H
#define Renderable_H

#include <Display.hpp>

class Renderable {
public:    
    virtual ~Renderable();
    virtual void update();
    virtual void render(Display &display, unsigned short int current_menu_position);
private:
    
};

#endif