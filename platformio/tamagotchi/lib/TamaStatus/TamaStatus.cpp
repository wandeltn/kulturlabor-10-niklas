#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <SPI.h>
#include <functional>

extern Timer timer;

TamaStatus::TamaStatus()
{

    timer.attach(&poop_timeable);
}

void TamaStatus::add_diet_counter(short int amount)
{
    Serial.print("old diet_helth_counter: ");
    Serial.println(diet_health_counter);
    health += diet_health_counter;
    Serial.print("adding amount to diet_health_counter: ");
    Serial.println((int)amount);
    diet_health_counter += amount;
    Serial.print("new diet_health_counter: ");
    Serial.println(diet_health_counter);
}

void TamaStatus::toggle_light()
{
    light_on = !light_on;
}

void TamaStatus::toggle_light(bool on)
{
    light_on = on;
}

void TamaStatus::clear_poop()
{
    poop_on_screen = 0;
}

short int TamaStatus::happyness = 0;
short int TamaStatus::health = 0;
short int TamaStatus::hunger = 0;
short int TamaStatus::poop_on_screen = 4;
short int TamaStatus::dicipline = 0;
short int TamaStatus::weight = 50;
short int TamaStatus::diet_health_counter = 0;
short int TamaStatus::care_errors = 0;
bool TamaStatus::sleeping = false;
bool TamaStatus::light_on = false;
Timeable TamaStatus::poop_timeable = {
    10000,
    &poop_on_screen,
    1, 
    std::function<void()>(TamaStatus::clear_poop)
};