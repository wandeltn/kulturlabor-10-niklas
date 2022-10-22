#include <Timer.hpp>
#include <SPI.h>

extern bool schedule_rerender;

void Timer::attach(Timeable* timer) {
    timer_list.push_back(timer);
}

void Timer::check_timer_list() {
    for (Timeable* list_item : timer_list) {
        if (list_item->call_time >= millis()) { //
            *list_item->linked_value += list_item->payload;
            schedule_rerender = true;
        }
    }
}