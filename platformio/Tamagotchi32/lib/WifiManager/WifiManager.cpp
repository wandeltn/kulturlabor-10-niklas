#include <WifiManager.hpp>
#include <Preferences.h>

#define AP_NAME         "Tamagotchi"
#define CONNECT_TIMEOUT 10000

WifiManager::WifiManager()
{
    readCredentials();  

    for (short i = 0; i <= sizeof(ssid_array) / sizeof(ssid_array[0]); i++) {
        wifiMulti.addAP(ssid_array[i].c_str(), password_array[i].c_str());
    }  
}

void WifiManager::begin(WiFiMode_t wifiMode)
{
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.disconnect();
    }
    if (wifiMode == WIFI_STA) {
        wifiMulti.run(CONNECT_TIMEOUT);
    } else if (wifiMode == WIFI_AP) {
        WiFi.mode(WIFI_AP);
        WiFi.softAP(AP_NAME);  
    }
}

void WifiManager::end()
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);

    writeCredentials();
}

void WifiManager::readCredentials()
{
    preferences.begin("credentials", true);

    ssid_array[0] = preferences.getString("ssid0");
    password_array[0] = preferences.getString("password0");
    ssid_array[1] = preferences.getString("ssid1");
    password_array[1] = preferences.getString("password1");
    ssid_array[2] = preferences.getString("ssid2");
    password_array[2] = preferences.getString("password2");
    ssid_array[3] = preferences.getString("ssid3");
    password_array[3] = preferences.getString("password3");
    ssid_array[4] = preferences.getString("ssid4");
    password_array[4] = preferences.getString("password4");
    ssid_array[5] = preferences.getString("ssid5");
    password_array[5] = preferences.getString("password5");
    ssid_array[6] = preferences.getString("ssid6");
    password_array[6] = preferences.getString("password6");

    preferences.end();
}

void WifiManager::writeCredentials()
{
    preferences.begin("credentials");

    preferences.putString("ssid0", ssid_array[0]);
    preferences.putString("password0", password_array[0]);
    preferences.putString("ssid1", ssid_array[1]);
    preferences.putString("password1", password_array[1]);
    preferences.putString("ssid2", ssid_array[2]);
    preferences.putString("password2", password_array[2]);
    preferences.putString("ssid3", ssid_array[3]);
    preferences.putString("password3", password_array[3]);
    preferences.putString("ssid4", ssid_array[4]);
    preferences.putString("password4", password_array[4]);
    preferences.putString("ssid5", ssid_array[5]);
    preferences.putString("password5", password_array[5]);
    preferences.putString("ssid6", ssid_array[6]);
    preferences.putString("password6", password_array[6]);

    preferences.end();
}

void WifiManager::switchMode(WiFiMode_t newMode)
{
    if (WiFi.getMode() != newMode) {
        WiFi.disconnect();

        if (newMode == WIFI_STA) {
            
        } else if (newMode == WIFI_AP) {
            WiFi.mode(WIFI_AP);
            WiFi.softAP(AP_NAME);  
        }
    }
}

void WifiManager::getPasswords(int*, char**)
{
    
}

void WifiManager::addPassword(char*, char*)
{
    
}

void WifiManager::removePassword(int)
{
    
}

WiFiMulti WifiManager::wifiMulti;
Preferences WifiManager::preferences;