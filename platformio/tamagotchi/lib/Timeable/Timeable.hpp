#ifndef Timeable_H
#define Timeable_H

#include <functional>
struct Timeable
{
    public:
        ~Timeable();

        unsigned long int call_time;
        short int* linked_value;
        short int payload;
        //std::function<void()> notifier;
        void(*notifier)();
};

#endif