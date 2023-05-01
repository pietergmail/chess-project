#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

// rotated for some reason, not sure why
char keys[ROWS][COLS] = {
  {'1','5','A','E'},
  {'2','6','B','F'},
  {'3','7','C','G'},
  {'4','8','D','H'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// get's the 2 chess coordinates
void checkinput() {
  char key1 = '\0';
  char key2 = '\0';
  while(key1 == '\0' || (key1 < 'A' || key1 > 'H')) {
    key1 = keypad.getKey(); // Read the first key
  }

  while(key2 == '\0' || (key2 < '0' || key2 > '8')) {
    key2 = keypad.getKey(); // Read the second key
  }

  coordinates[0] = key1;
  coordinates[1] = key2;

  // Print the two keys together
  Serial.print("Coordinate: ");
  for(int i=0; i<2; i++) {
    Serial.print(coordinates[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Send the characters to the arduino mega
}
