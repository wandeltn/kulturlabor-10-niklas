#ifndef GFX_H
#define GFX_H

#include <Adafruit_SSD1306.h>

class Display: public Adafruit_SSD1306 {
    public:
        Display(
            uint8_t w,
            uint8_t h,
            int8_t mosi_pin,
            int8_t sclk_pin,
            int8_t dc_pin,
            int8_t rst_pin,
            int8_t cs_pin
            );

        void drawInvertBitmapColor(int16_t x, int16_t y,
            const uint8_t *bitmap, int16_t w, int16_t h,
            uint16_t color);
};

#endif