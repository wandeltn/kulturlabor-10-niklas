#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <SPI.h>
#include <functional>

extern Timer timer;

#define POOP_INTERVAL_TIME_MS           10000
#define HUNGER_INTERVAL_TIME_MS         12000
#define HAPPYNESS_INTERVAL_TIME_MS      15000
#define HEALTH_INTERVAL_TIME_MS         20000
#define DICIPLINE_INTERVAL_TIME_MS      11000
#define WEIGHT_CHECK_INTERVAL_TIME_MS   50000
#define SLEEP_INTERVAL_TIME_MS          60000
#define DEATH_UPDATE_INTERVAL_TIME_MS   100000

TamaStatus::TamaStatus()
{
    updatePoopTimer();
    updateHungerTimer();
    updateHappynessTimer();
    updateHealthTimer();
    updateDiciplineTimer();
    updateWeghtCheckTImer();
    updateSleepTimer();
    updateDeathTimer();
}

void TamaStatus::add_diet_counter(short int amount)
{
    health += diet_health_counter;
    diet_health_counter += amount;
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
    #ifdef DEBUG
    Serial.println("clearing poop");
    #endif
    poop_on_screen = 0;
}

void TamaStatus::updatePoopTimer()
{
    #ifdef DEBUG
    Serial.println("Setting new poop Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            millis() + POOP_INTERVAL_TIME_MS - 500,
            millis() + POOP_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &poop_on_screen,
        .payload = 1,
        .notifier = &updatePoopTimer
    });
}

void TamaStatus::updateHungerTimer()
{
    #ifdef DEBUG
    Serial.println("Setting new hunger Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            millis() + HUNGER_INTERVAL_TIME_MS - 500,
            millis() + HUNGER_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &hunger,
        .payload = (short int)-round(getPolynomialValue()),
        .notifier = &updateHungerTimer
    });
}

void TamaStatus::updateHappynessTimer()
{
    #ifdef DEBUG
    Serial.println("Setting new happyness Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            millis() + POOP_INTERVAL_TIME_MS - 500,
            millis() + POOP_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &happyness,
        .payload = -10,
        .notifier = &updatePoopTimer
    });
}

void TamaStatus::updateHealthTimer()
{
    // TODO: correct sickness generation
    #ifdef DEBUG
    Serial.println("Setting new sickness Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            millis() + HEALTH_INTERVAL_TIME_MS - 500,
            millis() + HEALTH_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &health,
        .payload = -10,
        .notifier = &updateHealthTimer
    });
}

void TamaStatus::updateDiciplineTimer()
{
    #ifdef DEBUG
    Serial.println("Setting new dicipline Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            millis() + DICIPLINE_INTERVAL_TIME_MS - 500,
            millis() + DICIPLINE_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &dicipline,
        .payload = -5,
        .notifier = &updateDiciplineTimer
    });
}

void TamaStatus::updateWeghtCheckTImer()
{
    if (-500 >= hunger) {
        weight += hunger; // 1500
    } else if ( 500 <= hunger) {
        weight += hunger; // 1500 
    }
    #ifdef DEBUG
    Serial.println("Setting new weightCheck Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            millis() + WEIGHT_CHECK_INTERVAL_TIME_MS - 500,
            millis() + WEIGHT_CHECK_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &weight,
        .payload = 0,
        .notifier = &updateDiciplineTimer
    });
}

void TamaStatus::updateSleepTimer()
{
    sleeping = !sleeping;
    #ifdef DEBUG
    Serial.println("Setting new sleep Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            millis() + SLEEP_INTERVAL_TIME_MS - 500,
            millis() + SLEEP_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &health,
        .payload = 5,
        .notifier = &updateSleepTimer
    });
}

void TamaStatus::updateDeathTimer()
{
    #ifdef DEBUG
    Serial.println("Setting new deathCheck Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            millis() + DEATH_UPDATE_INTERVAL_TIME_MS - 500,
            millis() + DEATH_UPDATE_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &weight,
        .payload = 0,
        .notifier = &updateDiciplineTimer
    });
}

double TamaStatus::getPolynomialValue()
{
    double terms[4] = {
        9.9999999999997874e+002,
        5.9151704397609030e-003,
        -5.5089670016536930e-009,
        1.3956521653067459e-015
    };
    int t = 0;
    double result = 0;
    for (unsigned int c = 0; c < (sizeof(terms) / sizeof(terms[0])); c++) {
        result += terms[c] * t;
        t *= millis() / 1000; // convert millis to seconds
    }
    return result * 1000; // convert back to millis
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