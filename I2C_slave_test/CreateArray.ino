// Function to generate random values for the array
void generateRandomArray() {
  randomSeed(analogRead(A0)); // Seed the random number generator
  for (int i = 0; i < ARRAY_ROWS; i++) {
    for (int j = 0; j < ARRAY_COLS; j++) {
      myArray[i][j] = random(0, 13); // Generate random value between 0 and 12
    }
  }
}
