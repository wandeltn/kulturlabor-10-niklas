#ifndef __TAMASTATUS_H__
#define __TAMASTATUS_H__

#include <Timeable.hpp>
#include <iostream>
#include <ImageFormat.hpp>
#include <Vector2.hpp>
#include <storage/settings_nvs.h>

class TamaStatus {
    public:
        TamaStatus();
        static short int poop_on_screen;
        static short int hunger;
        static short int happyness;
        static short int health;
        static short int dicipline;
        static short int weight;
        static bool light_on;

//         static long random(long start, long end);
        static void begin();
        static void end();
        static void reset();
        static void recoverSleep(long shutdown_time);
        static void errorCheck(esp_err_t);
        static void add_diet_counter(short int amount);
        static void toggle_light();
        static void toggle_light(bool on);
        static void clear_poop();

        static void updatePoopTimer();
        static void updateHungerTimer();
        static void updateHappynessTimer();
        static void updateHealthTimer();
        static void updateDiciplineTimer();
        static void updateWeghtCheckTImer();
        static void updateSleepTimer();
        static void updateDeathTimer();
        static void updatePositionTimer();
        static void updateEvolutionTimer();
        static void updateSicknessTimer();

        static void updateJump();
        static double getPolynomialValue(time_t time_in_seconds);
        static std::string getSickness();

        static ImageFormat current_display_state;
        static Vector2 position;
        static Vector2 velocity;
    private:
        static short current_sickness;
        inline static const std::string sicknesses[9] = {
            "Healthy",
            "Headaches",
            "Flu",
            "Fever",
            "Nausea",
            "Vomiting"
            "Insomnia",
            "Depression",
            "COVID-19"
        };
        static uint64_t evolve_time;
        static constexpr double gravity = 9.8;
        static short int diet_health_counter;
        static short int care_errors;
        static int16_t evolution_state;
        static int16_t display_state;
        static bool sleeping;
        static bool jumping;
};

#endif // __TAMASTATUS_H__