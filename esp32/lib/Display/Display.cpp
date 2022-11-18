#include <Display.hpp>

Display::Display(
    uint8_t w,
    uint8_t h,
    int8_t mosi_pin,
    int8_t sclk_pin,
    int8_t dc_pin,
    int8_t rst_pin,
    int8_t cs_pin
    ) : Adafruit_SSD1306(
        w,
        h,
        mosi_pin,
        sclk_pin,
        dc_pin,
        rst_pin,
        cs_pin
    )
{
    
}

void Display::drawInvertBitmapColor(int16_t x, int16_t y,
            const uint8_t *bitmap, int16_t w, int16_t h,
            uint16_t color) {

  int16_t byteWidth = (w + 7) / 8;

  startWrite();
  for(int16_t j=0; j<h; j++) {
    for(int16_t i=0; i<w; i++ ) {
      if((pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)))==0) {
        writePixel(x+i, y+j, color);
      }
    }
  }
  endWrite();
}