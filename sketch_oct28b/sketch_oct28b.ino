#include <Adafruit_NeoPixel.h>
#define LEDPIN 12
#define NUMBER_PIXELS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

const int TrigPin = 2;
const int EchoPin = 3;
float cm;
int delayTime = 200;
int wait = 500;
int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  strip.begin();
  pinMode(LED_BUILTIN, OUTPUT);


  // turn the strip on
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
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

void loop() {
  // for (int i = 0; i < NUMBER_PIXELS; i++) {
  //   strip.setPixelColor(i, 50, 50, 50);
  //   Serial.println(i);
  //   delay(200);
  //   strip.show();
  // }
  // strip.clear();

  cm = pulseIn(EchoPin, HIGH) / 58.0;  //The echo time is converted into cm
  cm = (int(cm * 100.0)) / 100.0;
  // Keep two decimal places
  // Serial.println(cm);

  // if (cm < 100) {
  if (true) {
    // starting at i, draw the 7 color rainbow
    // a seven segment rainbow with red on the highest pixel
    for (int i = 0; i < 999999999; i++) {
      i %= NUMBER_PIXELS;
      rainbow7(i);
      strip.show();
      delay(wait);
      strip.clear();
      strip.show();
    }
  } else {
    strip.clear();
    strip.show();
  }
}
