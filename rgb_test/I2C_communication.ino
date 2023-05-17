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

  // request data for the lcd()
  Wire.requestFrom(I2C_ADDRESS, 64);
  uint8_t buffer[32];
  uint8_t i = 0;
  while (Wire.available()) {
    buffer[i++] = Wire.read();
  }

  // build string from data
  lcdstring = "";
  for (uint8_t j = 0; j < 32; j++) {
    if (isPrintable(buffer[j])) {
      lcdstring += char(buffer[j]);
    } else {
      // if not printable, string done
      break;
    }
  }
  Serial.println(lcdstring);
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
  Serial.println(coordinates[0]);
  Serial.println(coordinates[1]);
  Wire.beginTransmission(I2C_ADDRESS); // transmit to device with address 0x08
  Wire.write(coordinates, sizeof(coordinates)); // send the array over I2C
  Wire.endTransmission(); // stop transmitting
}