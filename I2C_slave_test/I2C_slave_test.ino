#include <Wire.h>
#include <stdlib.h> // Required for random() function

// Define the I2C address of the receiver
const int I2C_ADDRESS = 0x08; // Replace with the actual I2C address of the receiver

// Define the size of the array
const int ARRAY_ROWS = 4;
const int ARRAY_COLS = 8;

// Define the array to be sent
byte myArray[ARRAY_ROWS][ARRAY_COLS];

void setup() {
  Serial.begin(9600);
  // Start the I2C communication as a slave with the given address
  Wire.begin(I2C_ADDRESS);
  // Define callback functions for I2C events
  Wire.onRequest(requestEvent);
  
  // Generate random values for the array
  generateRandomArray();
}

void loop() {
  generateRandomArray();
  delay(1000);
  // Do nothing
}

// Function to generate random values for the array
void generateRandomArray() {
  randomSeed(analogRead(A0)); // Seed the random number generator
  for (int i = 0; i < ARRAY_ROWS; i++) {
    for (int j = 0; j < ARRAY_COLS; j++) {
      myArray[i][j] = random(0, 13); // Generate random value between 0 and 12
    }
  }
}

// I2C request event callback function
void requestEvent() {
  Serial.println("Data requested");
  // Send the array over I2C
  for (int i = 0; i < ARRAY_ROWS; i++) {
    for (int j = 0; j < ARRAY_COLS; j++) {
      Wire.write(myArray[i][j]);
    }
  }
}
