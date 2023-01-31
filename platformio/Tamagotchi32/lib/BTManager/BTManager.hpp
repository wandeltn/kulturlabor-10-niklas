#ifndef __BTMANAGER_H__
#define __BTMANAGER_H__

#include <UMS3.h>
#include <BLEScan.h>

class BTManager {
    public:
        BTManager();
        void begin();
        void enable();
        void disable();
        bool getBTStatus();
        uint8_t getNearbyDevices();
    private:
        static BLEScan* pBLEScan;
};

#endif // __BTMANAGER_H__