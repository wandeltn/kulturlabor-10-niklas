#ifndef Timer_H
#define Timer_H

#include <vector>
#include <Timeable.hpp>

class Timer {
    public:        
        void attach(Timeable* timer);
        void check_timer_list();
    private:
        std::vector<Timeable*> timer_list;
};

#endif