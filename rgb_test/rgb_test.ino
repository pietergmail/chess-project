#include <FastLED.h>
#include <Wire.h>

#define NUM_STRIPS 1
#define NUM_LEDS_PER_STRIP 64

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
// create representation of all the pieces
int pieces1[4][8]; // top half
int pieces2[4][8]; // bottom half
int pieces[8][8]; //full chess board
char coordinates[2]; // coordinates used for sending

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
  FastLED.setBrightness(20);
  // tell FastLED there's 64 NEOPIXEL leds on pin 5
  FastLED.addLeds<NEOPIXEL, 10>(leds[0], NUM_LEDS_PER_STRIP);
  Serial.begin(9600);
}

void loop() {
  checkinput();
  sendData();
  // select move
  checkinput();
  sendData();
  // receive new board
  receiveData();
  combineArrays(pieces1, pieces2, pieces);
  // print data to the the led array
  ArrayToLeds(pieces);
  
}
