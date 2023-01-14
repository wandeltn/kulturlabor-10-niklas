#ifndef __MEDICINESCREEN_H__
#define __MEDICINESCREEN_H__

#include <BaseScreen.hpp>

class MedicineScreen: public BaseScreen {
    public:
        MedicineScreen();
        void onButtonBPressed();
        inline static const char* display_options[4] = {
        "  Vaccination",
        "  Medicine",
        "  Doctor",
        "  Exit"
        };
    private:
};

#endif // __MEDICINESCREEN_H__