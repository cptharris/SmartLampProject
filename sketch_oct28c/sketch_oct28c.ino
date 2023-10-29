#include <Adafruit_NeoPixel.h>
#define LEDPIN 12
#define NUMBER_PIXELS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
}

void rainbow7(uint16_t i) {
  // we use the modulo function with this
  // strip.setPixelColor((i + 0) % NUMBER_PIXELS, 000, 000, 000);  // off
  strip.setPixelColor((i + 1) % NUMBER_PIXELS, 025, 000, 025);  // violet
  strip.setPixelColor((i + 2) % NUMBER_PIXELS, 255, 000, 255);  // indigo
  strip.setPixelColor((i + 3) % NUMBER_PIXELS, 000, 000, 150);  // blue
  strip.setPixelColor((i + 4) % NUMBER_PIXELS, 000, 150, 000);  // green
  strip.setPixelColor((i + 5) % NUMBER_PIXELS, 255, 255, 000);  // yellow
  strip.setPixelColor((i + 6) % NUMBER_PIXELS, 110, 070, 000);  // orange
  strip.setPixelColor((i + 7) % NUMBER_PIXELS, 150, 000, 000);  // red
  if (i < NUMBER_PIXELS * 2) {
    rainbow7(i + 7);
  }
}

void threeOn(uint16_t i) {
  strip.setPixelColor((i - 1) % NUMBER_PIXELS, 50, 50, 50);
  strip.setPixelColor((i + 0) % NUMBER_PIXELS, 50, 50, 50);
  strip.setPixelColor((i + 1) % NUMBER_PIXELS, 50, 50, 50);
  if (i < NUMBER_PIXELS * 2) {
    threeOn(i + 5);
  }
}

void loop() {

  for (int i = 0; i < NUMBER_PIXELS; i++) {
    rainbow7(i);
    strip.show();
    delay(500);
    strip.clear();
    strip.show();
  }

  // for (int i = 0; i < 1000; i++) {
  //   i %= NUMBER_PIXELS;
  //   rainbow7(i);
  //   strip.show();
  //   delay(500);
  //   strip.clear();
  //   strip.show();
  // }
}
