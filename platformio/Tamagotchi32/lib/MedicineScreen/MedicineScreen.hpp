#ifndef __MEDICINESCREEN_H__
#define __MEDICINESCREEN_H__

#include <BaseScreen.hpp>

class MedicineScreen: public BaseScreen {
    public:
        MedicineScreen();
        void onButtonBPressed();
        inline static const char* display_options[3] = {
        "  Vaccination",
        "  Medicine",
        "  Doctor"
        };
    private:
};

#endif // __MEDICINESCREEN_H__