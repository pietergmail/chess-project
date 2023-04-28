#include <Wire.h>

// Define the I2C address of the receiver
const int I2C_ADDRESS = 0x08; // Replace with the actual I2C address of the receiver

// Define the size of the arrays
const int ARRAY_ROWS = 4;
const int ARRAY_COLS = 8;

void receiveData() {
  // Request data for the first array from the I2C slave
  Wire.requestFrom(I2C_ADDRESS, ARRAY_ROWS * ARRAY_COLS);
  
  // Read and print the received data for the first array
  for (int i = 0; i < ARRAY_ROWS; i++) {
    for (int j = 0; j < ARRAY_COLS; j++) {
      if (Wire.available()) {
        pieces1[i][j] = Wire.read();
      }
    }
  }
  
  // Request data for the second array from the I2C slave
  Wire.requestFrom(I2C_ADDRESS, ARRAY_ROWS * ARRAY_COLS);
  
  // Read and print the received data for the second array
  for (int i = 0; i < ARRAY_ROWS; i++) {
    for (int j = 0; j < ARRAY_COLS; j++) {
      if (Wire.available()) {
        pieces2[i][j] = Wire.read();
      }
    }
  }
}

void combineArrays(int arr1[4][8], int arr2[4][8], int arr3[8][8]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      arr3[i][j] = arr1[i][j];           // Copy elements from the first array to the combined array
      arr3[i + 4][j] = arr2[i][j];       // Copy elements from the second array to the combined array
    }
  }
}

void sendData() {
  Wire.beginTransmission(I2C_ADDRESS); // transmit to device with address 0x08
  Wire.write(coordinates, sizeof(coordinates)); // send the array over I2C
  Wire.endTransmission(); // stop transmitting
}
