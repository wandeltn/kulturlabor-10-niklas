#include <SPI.h>
#include <UMS3.h>
#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <functional>
#include <Bitmaps.hpp>
#include <iterator>

extern Timer timer;
extern bool screen_on;

#define POOP_INTERVAL_TIME_MS           13000
#define HUNGER_INTERVAL_TIME_MS         12000
#define HAPPYNESS_INTERVAL_TIME_MS      15000
#define HEALTH_INTERVAL_TIME_MS         20000
#define DICIPLINE_INTERVAL_TIME_MS      11000
#define WEIGHT_CHECK_INTERVAL_TIME_MS   50000
#define SLEEP_INTERVAL_TIME_MS          10000
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
    updatePositionTimer();
    updateEvolutionTimer();
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
    Serial.print("poly function: ");
    Serial.println(getPolynomialValue());
    Serial.println((int)(round(getPolynomialValue()) * -1));
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            millis() + HUNGER_INTERVAL_TIME_MS - 500,
            millis() + HUNGER_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &hunger,
        .payload = (short)(round(getPolynomialValue()) * -1),
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
    updatePositionTimer();
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

void TamaStatus::updatePositionTimer()
{ 
    if (!jumping && !sleeping){
        jumping = true;
        velocity = {(double)random(-10, 10), -20};
    } else {
        velocity = {0, velocity.y};
    }
    #ifdef DEBUG
    Serial.println("getting new jump pos");
    #endif
    updateJump();    

    #ifdef DEBUG
    Serial.println("setting new timer");
    #endif
    if (screen_on && !sleeping) {
        timer.attach(new Timeable{
            .call_time = millis() + 0,
            .linked_value = &care_errors,
            .payload = 0,
            .notifier = &updatePositionTimer
        }); 
    }
}

void TamaStatus::updateEvolutionTimer()
{
    Serial.println("evolving");
    if (evolution_state < 5) {
        current_display_state = Bitmaps::Tama::evolution_list[evolution_state][random(Bitmaps::Tama::state_count[evolution_state] - 1)];
        timer.attach(new Timeable{
            .call_time = (unsigned long)(millis() + round(getPolynomialValue() * 30 * 1000)),
            .linked_value = &evolution_state,
            .payload = 1,
            .notifier = &updateEvolutionTimer
        });
    }
}

void TamaStatus::updateJump()
{
        double delta = 0.1; // time delta [s]

        velocity.x = velocity.x + delta * 0.0; // V_f = V_i + a * t
        velocity.y = velocity.y + delta * gravity; // V_f = V_i + a * t
        position.x = position.x + delta * velocity.x; // distance [m] = speed [m/s] * time [s]
        position.y = position.y + delta * velocity.y; // distance [m] = speed [m/s] * time [s]
        
        if (position.x >= 62 || position.x <= 20) {
            velocity.x *= -1;
        }

        if (position.y >= 16.0)
        {
            position.y = 16.0;
            jumping = false;
        }
        #ifdef DEBUG
        Serial.print("pos X: ");
        Serial.println(position.x);
        Serial.print("pos Y: ");
        Serial.println(position.y);
        #endif
}

double TamaStatus::getPolynomialValue()
{
    double terms[4] = {
        9.9999999999997874e+002,
        5.9151704397609030e-003,
        -5.5089670016536930e-009,
        1.3956521653067459e-015
    };
    double t = 1;
    double result = 0;
    for (unsigned int c = 0; c < (sizeof(terms) / sizeof(terms[0])); c++) {
        result += terms[c] * t;
        t *= millis() / 1000; // convert millis to seconds
    }
    return result; // convert back to millis
}

short int TamaStatus::happyness = 0;
short int TamaStatus::health = 0;
short int TamaStatus::hunger = 0;
short int TamaStatus::poop_on_screen = 4;
short int TamaStatus::dicipline = 0;
short int TamaStatus::weight = 50;
short int TamaStatus::diet_health_counter = 0;
short int TamaStatus::care_errors = 0;
short int TamaStatus::evolution_state = 0;

Vector2 TamaStatus::position = {
    .x = 40, 
    .y = 16
};
Vector2 TamaStatus::velocity = {
    .x = 0,
    .y = 20
};

bool TamaStatus::jumping = true;
bool TamaStatus::sleeping = false;
bool TamaStatus::light_on = false;
ImageFormat TamaStatus::current_display_state = Bitmaps::Tama::EggStage::egg_up_image;