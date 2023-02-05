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
        void connect();
        void readCredentials();
        void writeCredentials();
        void switchMode(WiFiMode_t);
        void getPasswords(int*, char**);
        void addPassword(char*, char*);
        void removePassword(int);

    private:
        static WiFiMulti wifiMulti;
        static Preferences preferences;
        inline static String ssid_array[7] = {};
        inline static String password_array[7] = {};
};

#endif // __WIFIMANAGER_H__