#include <Wire.h>
#include <stdlib.h> // Required for random() function

// Define the I2C address of the receiver
const int I2C_ADDRESS = 0x08; // Replace with the actual I2C address of the receiver

// input arrays with chess notation
char arr1[2]; // first array to store received data
char arr2[2]; // second array to store received data

// coordinates with normal notaions
int coo1[2];
int coo2[2];

// flag to determine which array to use
bool useArr1 = true; 

// Define the starting chess board
int chessBoard[8][8] = {
  {2, 3, 4, 5, 6, 4, 3, 2},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {7, 7, 7, 7, 7, 7, 7, 7},
  {8, 9, 10, 11, 12, 10, 9, 8}
};

// Define the arrays that will be send (board is to big needs to be split into 2
int myArray1[4][8];
int myArray2[4][8];

// flag to knowh wich array to send
int currentArray = 1;

void setup() {
  Serial.begin(9600);
  // Start the I2C communication as a slave with the given address
  Wire.begin(I2C_ADDRESS);
  // Define callback functions for I2C events
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
}
