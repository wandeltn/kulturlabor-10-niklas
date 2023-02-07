#include <TamaStatus.hpp>
#include <Timer.hpp>
#include <SPI.h>
#include <functional>
#include <Bitmaps.hpp>
#include <iterator>
#include <HardwareSerial.h>
#include <UMS3.h>
#include <storage/settings_nvs.h>
#include <BTManager.hpp>

extern Timer timer;
extern BTManager btManager;
extern bool screen_on;
extern bool schedule_rerender;
extern esp_err_t nvsError;
extern timeval tv;

#define POOP_INTERVAL_TIME_MS           13
#define HUNGER_INTERVAL_TIME_MS         10
#define HAPPYNESS_INTERVAL_TIME_MS      15
#define HEALTH_INTERVAL_TIME_MS         20
#define DICIPLINE_INTERVAL_TIME_MS      11
#define WEIGHT_CHECK_INTERVAL_TIME_MS   50  // muss für die wiederherstellung durch den wert von HUNGER teilbar sein 
#define SLEEP_INTERVAL_TIME_MS          10
#define DEATH_UPDATE_INTERVAL_TIME_MS   100
#define SICKNESS_UPDATE_INTERVAL_TIME   10

#define HUNGER_ADD_VALUE                -10
#define HAPPYNESS_ADD_VALUE             -10
#define HEALTH_ADD_VALUE                -10
#define DICIPLINE_ADD_VALUE             -5

TamaStatus::TamaStatus()
{

};

void TamaStatus::begin()
{
    nvsError = nvs_flash_init();
    if (nvsError == ESP_ERR_NVS_NO_FREE_PAGES || nvsError == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvsError = nvs_flash_init();
    }
    ESP_ERROR_CHECK( nvsError );

        // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle to Read only... ");
    nvs_handle_t my_handle;
    nvsError = nvs_open("storage", NVS_READONLY, &my_handle);
    if (nvsError != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(nvsError));
    } else {
        printf("Done\n");

        /* Read from NVS:     */
        printf("Reading length of first User Message from NVS ... ");

        nvsError = nvs_get_i16(my_handle, "evolution_state", &evolution_state);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "display_state", &display_state);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "happyness", &happyness);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "health", &health);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "hunger", &hunger);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "poop_on_screen", &poop_on_screen);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "dicipline", &dicipline);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "weight", &weight);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "diet_counter", &diet_health_counter);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "care_errors", &care_errors);
        errorCheck(nvsError);
        nvsError = nvs_get_i16(my_handle, "sickness", &current_sickness);
        errorCheck(nvsError);
        int64_t shutdown_time = 0;
        nvsError = nvs_get_i64(my_handle, "shutdown_time", &shutdown_time);
        errorCheck(nvsError);
        nvsError = nvs_get_u64(my_handle, "evolution_time", &evolve_time);
        recoverSleep(shutdown_time);

    // Close
    nvs_close(my_handle);
    }
    
    updatePoopTimer();
    updateHungerTimer();
    updateHappynessTimer();
    updateHealthTimer();
    updateDiciplineTimer();
    updateWeghtCheckTImer();
    updateSleepTimer();
    updateDeathTimer();
    updateEvolutionTimer();
    // updatePositionTimer();
}

void TamaStatus::end()
{
    btManager.enable();
    if (btManager.getNearbyDevices() >= 5) {
        current_sickness = 8; // get covid
    }
    yield();
        // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle to Write ... ");
    nvs_handle_t my_handle;
    nvsError = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (nvsError != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(nvsError));
    } else {
        printf("Done\n");
        // Write value into the NVS
        printf("Updating the length of first User Message in NVS ... ");

        nvsError = nvs_set_i16(my_handle, "evolution_state", evolution_state);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "display_state", display_state);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "happyness", happyness);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "health", health);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "hunger", hunger);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "poop_on_screen", poop_on_screen);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "dicipline", dicipline);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "weight", weight);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "diet_counter", diet_health_counter);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "care_errors", care_errors);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i16(my_handle, "sickness", current_sickness);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i64(my_handle, "shutdown_time", tv.tv_sec);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");
        nvsError = nvs_set_i64(my_handle, "evolution_time", evolve_time);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");

        // Commit written value.
        // After setting any values, nvs_commit() must be called to ensure changes are written
        // to flash storage. Implementations may write to storage at other times,
        // but this is not guaranteed.
        printf("Committing updates in NVS ... ");
        nvsError = nvs_commit(my_handle);
        printf((nvsError != ESP_OK) ? "Failed!\n" : "Done\n");

        // Close
        nvs_close(my_handle);
   }
}

void TamaStatus::reset()
{
    evolution_state = 0;
    happyness = 0;
    health = 0;
    hunger = 0;
    poop_on_screen = 4;
    dicipline = 0;
    weight = 50;
    diet_health_counter = 0;
    care_errors = 0;
    schedule_rerender = true;
}

void TamaStatus::recoverSleep(long shutdown_time)
{
    long current_time = tv.tv_sec;
    long simulated_time = shutdown_time;
    // sleep
    while (simulated_time <= current_time) {
        sleeping = !sleeping;
        simulated_time += (unsigned long)(random(
            tv.tv_sec + SLEEP_INTERVAL_TIME_MS - 500,
            tv.tv_sec + SLEEP_INTERVAL_TIME_MS + 500
        ));
    }
    simulated_time = shutdown_time;

    // happyness
    while (simulated_time <= current_time) {
        hunger += HUNGER_ADD_VALUE;
        simulated_time += random(
            simulated_time + POOP_INTERVAL_TIME_MS - 500,
            simulated_time + POOP_INTERVAL_TIME_MS + 500
        );
    }
    simulated_time = shutdown_time;

    //health
    while (simulated_time <= current_time) {
        health += HEALTH_ADD_VALUE;
        simulated_time += random(
            simulated_time + HEALTH_INTERVAL_TIME_MS - 500,
            simulated_time + HEALTH_INTERVAL_TIME_MS + 500
        );
    }
    simulated_time = shutdown_time;
    int hunger_interations = 0;
    // hunger
    while (simulated_time <= current_time) {
        hunger -= getPolynomialValue(simulated_time);
        simulated_time += random(
            simulated_time + HUNGER_INTERVAL_TIME_MS - 500,
            simulated_time + HUNGER_INTERVAL_TIME_MS + 500
        );
        if (hunger_interations % 5 == 0) {
            if (-2000 >= hunger) {
                weight += hunger / 500; // 1500
            } else if ( 2000 <= hunger) {
                weight += hunger / 500; // 1500 
            }
        }
    }
    simulated_time = shutdown_time;

    //poop_on_screen
    while (simulated_time <= current_time) {
        poop_on_screen += 1;
        simulated_time += random(
            simulated_time + HEALTH_INTERVAL_TIME_MS - 500,
            simulated_time + HEALTH_INTERVAL_TIME_MS + 500
        );
    }
    simulated_time = shutdown_time;

    //dicipline
    while (simulated_time <= current_time) {
        dicipline += DICIPLINE_ADD_VALUE;
        simulated_time += random(
            simulated_time + DICIPLINE_INTERVAL_TIME_MS - 500,
            simulated_time + DICIPLINE_INTERVAL_TIME_MS + 500
        );
    }
    simulated_time = shutdown_time;

    //care_errors
}

void TamaStatus::errorCheck(esp_err_t)
{
    switch (nvsError) {
        case ESP_OK:
            printf("Done\n");
            printf("First User Message = %d\n", evolution_state);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("The value is not initialized yet!\n");
            break;
        default :
            printf("Error (%s) reading!\n", esp_err_to_name(nvsError));
    }
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
            esp_timer_get_time() + POOP_INTERVAL_TIME_MS - 500,
            esp_timer_get_time() + POOP_INTERVAL_TIME_MS + 500
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
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            tv.tv_sec + HUNGER_INTERVAL_TIME_MS - 500,
            tv.tv_sec + HUNGER_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &hunger,
        .payload = (short)(round(getPolynomialValue(tv.tv_sec)) * -1),
        .notifier = &updateHungerTimer
    });
}

void TamaStatus::updateHappynessTimer()
{
    #ifdef DEBUG
    Serial.println("Setting new happyness Timeable");
    #endif
    if (happyness < 0) {
        happyness = 0;
        current_sickness = 7;
        care_errors++;
    }
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            tv.tv_sec + POOP_INTERVAL_TIME_MS - 500,
            tv.tv_sec + POOP_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &happyness,
        .payload = HAPPYNESS_ADD_VALUE,
        .notifier = &updatePoopTimer
    });
}

void TamaStatus::updateHealthTimer()
{
    // TODO: correct sickness generation
    #ifdef DEBUG
    Serial.println("Setting new sickness Timeable");
    #endif
    if(health < 0) {
        health = 0;
        current_sickness = 9;
        care_errors++;
    }
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            tv.tv_sec + HEALTH_INTERVAL_TIME_MS - 500,
            tv.tv_sec + HEALTH_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &health,
        .payload = HEALTH_ADD_VALUE,
        .notifier = &updateHealthTimer
    });
}

void TamaStatus::updateDiciplineTimer()
{
    #ifdef DEBUG
    Serial.println("Setting new dicipline Timeable");
    #endif
    if(dicipline < 0) {
        dicipline = 0;
        care_errors++;
    }
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            tv.tv_sec + DICIPLINE_INTERVAL_TIME_MS - 500,
            tv.tv_sec + DICIPLINE_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &dicipline,
        .payload = DICIPLINE_ADD_VALUE,
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
    if (weight < 0) {
        weight = 0;
        care_errors++;
    }
    #ifdef DEBUG
    Serial.println("Setting new weightCheck Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            tv.tv_sec + WEIGHT_CHECK_INTERVAL_TIME_MS - 500,
            tv.tv_sec + WEIGHT_CHECK_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &weight,
        .payload = 0,
        .notifier = &updateDiciplineTimer
    });
}

void TamaStatus::updateSleepTimer()
{
    sleeping = !sleeping;
    // updatePositionTimer();
    #ifdef DEBUG
    Serial.println("Setting new sleep Timeable");
    #endif
    timer.attach(new Timeable{
        .call_time = (unsigned long)(random(
            tv.tv_sec + SLEEP_INTERVAL_TIME_MS - 5,
            tv.tv_sec + SLEEP_INTERVAL_TIME_MS + 5
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
            tv.tv_sec + DEATH_UPDATE_INTERVAL_TIME_MS - 500,
            tv.tv_sec + DEATH_UPDATE_INTERVAL_TIME_MS + 500
        )),
        .linked_value = &weight,
        .payload = 0,
        .notifier = &updateDiciplineTimer
    });
}

// void TamaStatus::updatePositionTimer()
// {     
//     if (!jumping && !sleeping){
//         jumping = true;
//         velocity = {(double)random(-10, 10), -20};
//         // velocity = {0, (double)random(-5, -20)};
//         // velocity = {0, -20};
//     }
//     #ifdef DEBUG
//     Serial.println("getting new jump pos");
//     Serial.println(random(10, 20) - 30);
//     Serial.println(esp_random());
//     #endif
//     updateJump();    
//     schedule_rerender = true;
//     #ifdef DEBUG
//     Serial.println("setting new timer");
//     #endif

//     if (!sleeping) {
//         timer.attach(new Timeable{
//             .call_time = (unsigned long)tv.tv_sec + 100,
//             .linked_value = &care_errors,
//             .payload = 0,
//             .notifier = &updatePositionTimer
//         }); 
//     }
// }

void TamaStatus::updateEvolutionTimer()
{
    if (evolution_state >= sizeof(Bitmaps::Tama::state_count) / sizeof(Bitmaps::Tama::state_count[0])) {
        evolution_state = (sizeof(Bitmaps::Tama::state_count) / sizeof(Bitmaps::Tama::state_count[0]) - 1);
    } else {
        if (evolve_time <= tv.tv_sec) {
            // evolve_time = (unsigned long)(tv.tv_sec + 1000 * getPolynomialValue(tv.tv_sec));
            evolve_time = tv.tv_sec + 5;
        }
        timer.attach(new Timeable{
            .call_time = (unsigned long)evolve_time,
            //.call_time = (unsigned long)(tv.tv_sec + round(getPolynomialValue() * 30 * 1000)),
            .linked_value = &evolution_state,
            .payload = 1,
            .notifier = &updateEvolutionTimer
        });
    }
    if (evolve_time <= tv.tv_sec) {
        display_state = random(Bitmaps::Tama::state_count[evolution_state] - 1);
    }
    current_display_state = Bitmaps::Tama::evolution_list[evolution_state][display_state];
}

void TamaStatus::updateSicknessTimer()
{
    if (random(1, 50) == 1) {
        current_sickness = random(0, 5);
    }
    timer.attach(new Timeable{
        .call_time = SICKNESS_UPDATE_INTERVAL_TIME,
        .linked_value = nullptr,
        .payload = 0,
        .notifier = &updateSicknessTimer
    });
}

void TamaStatus::updateJump()
{
        double delta = 0.1; // time delta [s]

        velocity.x = velocity.x + delta * 0.0; // V_f = V_i + a * t
        velocity.y = velocity.y + delta * gravity; // V_f = V_i + a * t
        position.x = position.x + delta * velocity.x; // distance [m] = speed [m/s] * time [s]
        position.y = position.y + delta * velocity.y; // distance [m] = speed [m/s] * time [s]
        
        if (position.x >= 62 || position.x <= 20) {
            if (sleeping && position.x <= 30) {
                velocity.x = 0;
            }
            velocity.x *= -1;
        }

        if (position.y >= 16.0)
        {
            position.y = 16.0;
            if (!sleeping) { 
                velocity = {(double)random(-10, 10), -20};
            }

        }
        #ifdef DEBUG
        Serial.print("pos X: ");
        Serial.println(position.x);
        Serial.print("pos Y: ");
        Serial.println(position.y);
        #endif
}

double TamaStatus::getPolynomialValue(time_t time_in_seconds)
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
        t *= time_in_seconds; // convert millis to seconds
    }
    return result; // convert back to millis
}

std::string TamaStatus::getSickness()
{
    return sicknesses[current_sickness];
}

void TamaStatus::renameTama(std::string new_name)
{
    tama_name = new_name;
}

std::string* TamaStatus::getNameP()
{
    return &tama_name;
}

short int TamaStatus::happyness = 0;
short int TamaStatus::health = 0;
short int TamaStatus::hunger = 0;
short int TamaStatus::poop_on_screen = 4;
short int TamaStatus::dicipline = 0;
short int TamaStatus::weight = 50;
uint64_t TamaStatus::evolve_time = 0;
short int TamaStatus::diet_health_counter = 0;
short int TamaStatus::care_errors = 0;
short int TamaStatus::current_sickness = 0;
int16_t TamaStatus::evolution_state = 0;
int16_t TamaStatus::display_state = 0;

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
std::string TamaStatus::tama_name = "";
ImageFormat TamaStatus::current_display_state = Bitmaps::Tama::EggStage::egg_up_image;