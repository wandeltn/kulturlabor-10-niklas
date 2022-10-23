#ifndef __TAMASTATUS_H__
#define __TAMASTATUS_H__

#include <Timeable.hpp>
#include <ImageFormat.hpp>
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

        static double getPolynomialValue();

        static ImageFormat current_display_state;
    private:
        static short int diet_health_counter;
        static short int care_errors;
        static bool sleeping;
};

#endif // __TAMASTATUS_H__