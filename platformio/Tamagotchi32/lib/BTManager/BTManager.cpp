#include <BTManager.hpp>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define SCAN_TIME   5

BTManager::BTManager()
{
    
}

void BTManager::begin()
{
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(nullptr);
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);  // less or equal setInterval value
}

void BTManager::enable()
{
    btStart();
}

void BTManager::disable()
{
    btStop();
}

bool BTManager::getBTStatus()
{
    return btStarted();
}

uint8_t BTManager::getNearbyDevices()
{
    BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME, false);    
    uint32_t num_devices = foundDevices.getCount();
    pBLEScan->clearResults();
    return num_devices;
}

BLEScan* BTManager::pBLEScan;