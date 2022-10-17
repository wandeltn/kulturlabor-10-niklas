#pragma once

#ifndef Renderable_H
#define Renderable_H

#include <vector>

using namespace std;

class Renderable {
public:    
    virtual void render() = 0;

private:
    unsigned short int current_menu_position = 0;
    unsigned short int max_menu_position = 0;
};

#endif