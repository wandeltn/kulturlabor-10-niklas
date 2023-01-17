#include <Timer.hpp>
#include <SPI.h>
#include <algorithm>
#include <UMS3.h>

extern bool schedule_rerender;

void Timer::attach(Timeable* timer) {
    timer_list.push_back(timer);
}

void Timer::cancel(Timeable* timer)
{
    timer_list.erase(std::remove(
        timer_list.begin(),
        timer_list.end(),
        timer),
        timer_list.end()
    );
}

void Timer::check_timer_list() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    for (Timeable* list_item : timer_list) {;
        if (list_item->call_time <= tv.tv_sec) {
            #ifdef DEBUG
            Serial.println("finished timer");
            #endif
            if (list_item->linked_value != nullptr){
                *list_item->linked_value += list_item->payload;
            }
            list_item->notifier();
            delete list_item;
            timer_list.erase(std::remove(
                timer_list.begin(),
                timer_list.end(),
                list_item),
                timer_list.end()
            );
            schedule_rerender = true;
        }
    }
}

short Timer::get_timer_amount()
{
    return timer_list.size();
}