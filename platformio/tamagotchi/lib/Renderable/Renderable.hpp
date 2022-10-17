#pragma once

#ifndef Renderable_H
#define Renderable_H

#include <vector>

using namespace std;

class Renderable {
public:    
    virtual void render();

private:
    unsigned short int current_menu_position;
    unsigned short int max_menu_position;
};

#endif