#include <Timer.hpp>
#include <SPI.h>
#include <algorithm>

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
    for (Timeable* list_item : timer_list) {;
        if (list_item->call_time <= millis()) { 
            Serial.println("finished timer");
            *list_item->linked_value += list_item->payload;
            list_item->notifier();
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