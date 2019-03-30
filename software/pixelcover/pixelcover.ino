/**************************************************
 * PixelCover with 176 LEDS (UCS1904)
 * Based on NeoPixel library 
 **************************************************/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 11

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(176, PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  /*
   uint16_t i, j;
  for(j=254; j<255; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(255,25,0));
    }
    strip.show();
 strip.setBrightness(j);
    delay(10);
  }

    for(j=255; j>254; j--) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(255,25,0));
    }
    strip.show();
 strip.setBrightness(j);
    delay(10);
  }
*/
  wave2();
  
}



void wave1() {
  
  uint16_t i, j;
  uint32_t colorwave[] = {strip.Color(255,5,0),
    strip.Color(255,10,0), strip.Color(255,15,0),
    strip.Color(255,20,0), strip.Color(255,25,0),
    strip.Color(255,30,0), strip.Color(255,35,0),
    strip.Color(255,40,0), strip.Color(255,45,0),
    strip.Color(255,50,0), strip.Color(255,55,0)};
  
  for(j=0; j<88; j++){
    for(i=0; i<strip.numPixels(); i++) {
      uint16_t col = (i+j)%22;
      if(col > 10) {
        col = 21-col;
      }
      strip.setPixelColor(i, colorwave[col]);
    }
    strip.show();
    delay(10);
  }

}

void wave2() {
  
  uint16_t i, j, ncol;

  ncol = 30;
  
  for(j=0; j<1320; j++){
    for(i=0; i<89; i++) {
      uint16_t col = (i+j)%(2*ncol);
      if(col > (ncol-1)) {
        col = 2*ncol-1-col;
      }
      uint32_t clr = strip.Color(255, 5 + col*1,0);
      strip.setPixelColor(i, clr);
      strip.setPixelColor(176-i, clr);
    }
    strip.show();
    delay(20);
  }

}