#include <SPI.h>
#include <Wire.h>
#include <UMS3.h>
#include <storage/settings_nvs.h>
#include "driver/rtc_io.h"
#include <cmath>
#include <vector>
#include <UserInput.hpp>
#include <BaseScreen.hpp>
#include <MainScreen.hpp>
#include <Display.hpp>
#include <Renderable.hpp>
#include <Timer.hpp>
#include <Timeable.hpp>
#include <TamaStatus.hpp>

#define DEBUG
// #define DEMO_MODE

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  35
#define OLED_CLK   36
#define OLED_DC    6
#define OLED_CS    34
#define OLED_RESET 7
Display display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    OLED_MOSI,
    OLED_CLK,
    OLED_DC,
    OLED_RESET,
    OLED_CS
);

Timer timer{};
UMS3 ums3;
BaseScreen* active_screen;
static TamaStatus tamaStatus{};
extern UserInput userInput;
esp_err_t nvsError;

bool screen_on = true;
bool schedule_rerender = true;
esp_sleep_wakeup_cause_t wakeup_reason;
void shutdown() {
    tamaStatus.end();
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, LOW);
    rtc_gpio_pullup_en(GPIO_NUM_13);
    esp_deep_sleep_start();
}

void print_wakeup_reason(){

  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0 : ums3.setPixelColor(0x00FF00); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void loop() {
    print_wakeup_reason();
    if (screen_on) {
        if(schedule_rerender) {
            display.clearDisplay();
            active_screen->render(display);
            display.display();
            schedule_rerender = false;
        } else if (userInput.button_B_pressed) {
            #ifdef DEBUG
            Serial.println("B pressed");
            #endif
            active_screen->onButtonBPressed();
            userInput.button_B_pressed = false;
            schedule_rerender = true;
        } else {
            timer.check_timer_list();
        }
    } else {
        timer.check_timer_list();
        Serial.flush();
        shutdown();
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    wakeup_reason = esp_sleep_get_wakeup_cause();

    ums3.begin();
    ums3.setLDO2Power(true);
    ums3.setPixelBrightness(100);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
        #ifdef DEBUG
        Serial.println(F("SSD1306 allocation failed"));
        #endif
        for(;;); // Don't proceed, loop forever
    }

    userInput.begin();
    
    display.display();
    delay(1000);

    // Clear the buffer
    display.clearDisplay();
    display.dim(true);
    // init code
    active_screen = new MainScreen();

    display.display(); 

    tamaStatus.begin();   
}