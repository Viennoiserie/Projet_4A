#include <Adafruit_NeoPixel.h>

#define STRIPSIZE 20

void color_wipe(uint32_t c, uint8_t wait) {

  for(uint16_t i = 0; i < STRIPSIZE; i++) {

      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {

  uint16_t i, j;

  for(j = 0; j < 256; j++) {
    for(i = 0; i < STRIPSIZE; i++) {

      strip.setPixelColor(i, Wheel((i+j) & 255));
    }

    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout

void rainbow_cycle(Adafruit_Neopixel s1, s2, s3, s4, s5) {

  uint16_t i, j;

  for(j = 0; j < 256*5; j++) { // 5 cycles of all colors on wheel
    for(i = 0; i < STRIPSIZE; i++) {

      s1.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      s2.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      s3.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      s4.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      s5.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }

    strip.show();
    delay(500);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.

uint32_t wheel(byte WheelPos) {
  
  if(WheelPos < 85) {

   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if(WheelPos < 170) {

   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {

   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void color_wave(uint8_t wait) {

  int i, j, cycle;
  
  float ang, rsin, gsin, bsin, offset;

  static int tick = 0;
  
  cycle = STRIPSZE * 25;       // times around the circle ...

  while (++tick % cycle) {

    offset = map2PI(tick);

    for (i = 0; i < STRIPSIZE; i++) {

      ang = map2PI(i) - offset;

      rsin = sin(ang);
      gsin = sin(2.0 * ang / 3.0 + map2PI(int(stripsize/6)));
      bsin = sin(4.0 * ang / 5.0 + map2PI(int(stripsize/3)));

      strip.setPixelColor(i, strip.Color(trigScale(rsin), trigScale(gsin), trigScale(bsin)));
    }

    strip.show();
    delay(wait);
  }
}

