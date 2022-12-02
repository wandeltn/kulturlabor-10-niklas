#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <SPI.h>
#include <functional>
#include <Bitmaps.hpp>
#include <iterator>
#include <math.h>
#include <HardwareSerial.h>

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
}

long TamaStatus::random(long start, long end)
{
    long max_number = end - start;

    return (long)(max_number / UINT32_MAX * esp_random()) + start; 
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
        .call_time = (unsigned long)(esp_random(
            // esp_timer_get_time() + POOP_INTERVAL_TIME_MS - 500,
            // esp_timer_get_time() + POOP_INTERVAL_TIME_MS + 500
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
    #endif
    time_t now;
    time(&now);
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            now + HUNGER_INTERVAL_TIME_MS - 500,
            now + HUNGER_INTERVAL_TIME_MS + 500
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
    time_t now;
    time(&now);
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            now + POOP_INTERVAL_TIME_MS - 500,
            now + POOP_INTERVAL_TIME_MS + 500
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
    time_t now;
    time(&now);
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            now + HEALTH_INTERVAL_TIME_MS - 500,
            now + HEALTH_INTERVAL_TIME_MS + 500
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
    time_t now;
    time(&now);
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            now + DICIPLINE_INTERVAL_TIME_MS - 500,
            now + DICIPLINE_INTERVAL_TIME_MS + 500
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
    time_t now;
    time(&now);
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            now + WEIGHT_CHECK_INTERVAL_TIME_MS - 500,
            now + WEIGHT_CHECK_INTERVAL_TIME_MS + 500
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
    time_t now;
    time(&now);
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            now + SLEEP_INTERVAL_TIME_MS - 500,
            now + SLEEP_INTERVAL_TIME_MS + 500
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
    time_t now;
    time(&now);
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            now + DEATH_UPDATE_INTERVAL_TIME_MS - 500,
            now + DEATH_UPDATE_INTERVAL_TIME_MS + 500
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
        // velocity = {0, (double)random(-5, -20)};
        // velocity = {0, -20};
    }
    #ifdef DEBUG
    Serial.println("getting new jump pos");
    Serial.println(random(10, 20) - 30);
    Serial.println(esp_random());
    #endif
    Serial.println(random(-10, -20));
    updateJump();    

    #ifdef DEBUG
    Serial.println("setting new timer");
    #endif
    if (screen_on && !sleeping) {
        timer.attach(new Timeable{
            .call_time = millis() + 10,
            .linked_value = &care_errors,
            .payload = 0,
            .notifier = &updatePositionTimer
        }); 
    }
}

void TamaStatus::updateEvolutionTimer()
{
    time_t now;
    time(&now);
    current_display_state = Bitmaps::Tama::evolution_list[evolution_state][random(0, Bitmaps::Tama::state_count[evolution_state] - 1)];
    timer.attach(new Timeable{
        .call_time = (unsigned long)(now) + 3000,
        //.call_time = (unsigned long)(millis() + round(getPolynomialValue() * 30 * 1000)),
        .linked_value = &evolution_state,
        .payload = 1,
        .notifier = &updateEvolutionTimer
    });
}

void TamaStatus::updateJump()
{
        double delta = 0.1; // time delta [s]

        velocity.x = velocity.x + delta * 0.0; // V_f = V_i + a * t
        velocity.y = velocity.y + delta * gravity; // V_f = V_i + a * t
        position.x = position.x + delta * velocity.x; // distance [m] = speed [m/s] * time [s]
        position.y = position.y + delta * velocity.y; // distance [m] = speed [m/s] * time [s]
        
        // if (position.x >= 62 || position.x <= 20) {
        //     velocity.x *= -1;
        // }

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
    time_t now;
    time(&now);
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
        t *= now / 1000; // convert millis to seconds
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