#ifndef Timeable_H
#define Timeable_H

#include <functional>
struct Timeable
{
    public:
        ~Timeable();

        unsigned long int call_time;
        int16_t* linked_value;
        short int payload;
        //std::function<void()> notifier;
        void(*notifier)();
};

#endif