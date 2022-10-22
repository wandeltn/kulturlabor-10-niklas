#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <SPI.h>

extern Timer timer;

static Timeable poop_timeable = {
    1000,
    &TamaStatus::poop_on_screen,
    1
};

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
short int TamaStatus::poop_on_screen = 0;
short int TamaStatus::dicipline;
short int TamaStatus::weight;
short int TamaStatus::diet_health_counter;
short int TamaStatus::care_errors;
bool TamaStatus::sleeping;
bool TamaStatus::light_on;