#include <Adafruit_NeoPixel.h>
#define LEDPIN 12
#define NUMBER_PIXELS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

const int TrigPin = 3;
const int EchoPin = 2;
const int minCM = 20;
float cm;
int delayTime = 200;
int wait = 500;
int i = 0;

bool state = false;

unsigned long next_range_check = millis();

/*

*/

void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  strip.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void rainbow7(uint16_t i) {
  // we use the modulo function with this
  for (int s = 0; s < NUMBER_PIXELS / 6; s++) {
    strip.setPixelColor((s * 6 + i + 0) % NUMBER_PIXELS, 255, 000, 255);  // indigo
    strip.setPixelColor((s * 6 + i + 1) % NUMBER_PIXELS, 000, 000, 150);  // blue
    strip.setPixelColor((s * 6 + i + 2) % NUMBER_PIXELS, 000, 150, 000);  // green
    strip.setPixelColor((s * 6 + i + 3) % NUMBER_PIXELS, 255, 255, 000);  // yellow
    strip.setPixelColor((s * 6 + i + 4) % NUMBER_PIXELS, 110, 070, 000);  // orange
    strip.setPixelColor((s * 6 + i + 5) % NUMBER_PIXELS, 150, 000, 000);  // red
  }
}

float getCM() {
  // request data from rangefinder
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  // echo time is converted into cm
  return (int((pulseIn(EchoPin, HIGH) / 58.0) * 100.0)) / 100.0;
  // Keep two decimal places
}

void loop() {
  if (true || millis() >= next_range_check) {
    cm = getCM();
    Serial.print("\t");
    Serial.print(state);
    Serial.print("\t");
    Serial.println(cm);
    if (cm < minCM) {
      state = !state;
      next_range_check += 500;
    } else {
      next_range_check += 100;
    }
  }

  if (i >= NUMBER_PIXELS) {
    i = 0;
  }

  if (state) {
    rainbow7(i);
    i++;
  } else {
    strip.clear();
  }

  strip.show();
  delay(300);
}
