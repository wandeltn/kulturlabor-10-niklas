#include <Timer.hpp>
#include <SPI.h>

extern bool schedule_rerender;

void Timer::attach(Timeable* timer) {
    timer_list.push_back(timer);
}

void Timer::check_timer_list() {
    for (Timeable* list_item : timer_list) {
        Serial.println("checking timer");
        Serial.print("list_item call time: ");
        Serial.println(list_item->call_time);
        Serial.println(millis());
        if (list_item->call_time >= millis()) { 
            Serial.println("finished timer");
            *list_item->linked_value += list_item->payload;
            Serial.print("calling notifier: ");
            if (list_item->notifier) {
                Serial.println("notifier");
            }
            list_item->notifier();
            Serial.println("scheduling rerender");
            schedule_rerender = true;
        }
    }
}