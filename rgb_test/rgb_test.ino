#include <FastLED.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Library for LCD


#define NUM_STRIPS 1
#define NUM_LEDS_PER_STRIP 64

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
// create representation of all the pieces
int pieces1[4][8]; // top half
int pieces2[4][8]; // bottom half
int pieces[8][8]; //full chess board
char coordinates[2]; // coordinates used for sending

String lcdstring = "";

void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();

  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
  FastLED.setBrightness(20);
  // tell FastLED there's 64 NEOPIXEL leds on pin 5
  FastLED.addLeds<WS2811, 10>(leds[0], NUM_LEDS_PER_STRIP);
  Serial.begin(9600);

  receiveData();
  combineArrays(pieces1, pieces2, pieces);

  // print data to the the led array
  ArrayToLeds(pieces);

  // set current player on lcd
  lcd.setCursor(0, 1);         // move cursor to   (0, 1)
  lcd.print("Player: White");        // print message at (0, 1)
}

void loop() {
  // select piece
  checkinput();
  sendData();
  // select move
  checkinput();
  sendData();
  // wait for slave to be done
  delay(100);
  // receive new board
  receiveData();
  combineArrays(pieces1, pieces2, pieces);
  
  // print data to lcd
  LCD_display();
  
  // print data to the the led array
  ArrayToLeds(pieces);
}
