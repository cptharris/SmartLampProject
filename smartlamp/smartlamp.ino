#include <Adafruit_NeoPixel.h>
#define LEDPIN 12
#define NUMBER_PIXELS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

const unsigned int TrigPin = 3;
const unsigned int EchoPin = 2;
const int minCM = 20;
float cm;
const unsigned int wait = 300;
int i = 0;

unsigned int state = 0;
bool stateChanged = false;

void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  strip.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void rainbow(uint16_t i) {
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

void christmas(uint16_t i) {
  // https://coolors.co/da2c38-226f54-87c38f-f4f0bb-43291f\
  // https://coolors.co/f7f7f0-080712-0031a5-2e3d6a-9badcc
  for (int s = 0; s < NUMBER_PIXELS / 5; s++) {
    strip.setPixelColor((s * 5 + i + 0) % NUMBER_PIXELS, 247, 247, 240);  // baby powder
    strip.setPixelColor((s * 5 + i + 1) % NUMBER_PIXELS, 8, 7, 18);       // rich black
    strip.setPixelColor((s * 5 + i + 2) % NUMBER_PIXELS, 0, 49, 165);     // international klein blue
    strip.setPixelColor((s * 5 + i + 3) % NUMBER_PIXELS, 46, 61, 106);    // delft blue
    strip.setPixelColor((s * 5 + i + 4) % NUMBER_PIXELS, 155, 173, 204);  // powder blue
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
  cm = getCM();
  Serial.print("\t");
  Serial.print(state);
  Serial.print("\t");
  Serial.println(cm);
  if (cm < minCM && !stateChanged) {  // if cm is less than the trigger point && cm isn't being held low
    state++;
    stateChanged = true;
  } else if (cm >= minCM && stateChanged) {  // if cm goes above trigger point and cm was being held low
    stateChanged = false;
  }

  switch (state) {
    case 1:
      rainbow(i);
      break;
    case 2:
      christmas(i);
      break;
    default:
      state = 0;
      strip.clear();
      break;
  }

  if (state != 0) {
    i++;
    if (i >= NUMBER_PIXELS) {
      i = 0;
    }
  }

  strip.show();
  delay(wait);
}
