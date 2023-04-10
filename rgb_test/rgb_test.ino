#include <FastLED.h>
#include <Wire.h>

#define NUM_STRIPS 1
#define NUM_LEDS_PER_STRIP 64

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
// create representation of all the pieces
int pieces1[4][8];
int pieces2[4][8];
int pieces[8][8];

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
  FastLED.setBrightness(20);
  // tell FastLED there's 64 NEOPIXEL leds on pin 5
  FastLED.addLeds<NEOPIXEL, 5>(leds[0], NUM_LEDS_PER_STRIP);
  Serial.begin(9600);
}

void loop() {
  receiveData();
  combineArrays(pieces1, pieces2, pieces);
  ArrayToLeds(pieces);
}
