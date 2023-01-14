#ifndef __WIFIMANAGER_H__
#define __WIFIMANAGER_H__

#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiMulti.h>
#include <Preferences.h>

class WifiManager {
    public:
        WifiManager();
        void begin(WiFiMode_t);
        void end();
        void swichMode(WiFiMode_t);
        void getPasswords(int*, char**);
        void addPassword(char*, char*);
        void removePassword(int);

    private:
        inline static char* ssid_array[] = {};
        inline static char* password_array[] = {};
};

#endif // __WIFIMANAGER_H__