// Generates the new array, based on inputs
void generateArray() {
  // logic to move the piece
  movePiece(arr1, arr2);
  // print out error
  Serial.println(lcdString);
  // split the newly generated array in 2
  splitArray(chessBoard, myArray1, myArray2);


}

// Function that splits the array in 2
void splitArray(int inputArray[][8], int outputArray1[][8], int outputArray2[][8]) {
  // Determine the midpoint of the array
  int midpoint = 8 / 2;
  
  // Copy the first half of the input array to outputArray1
  for (int i = 0; i < midpoint; i++) {
    for (int j = 0; j < 8; j++) {
      outputArray1[i][j] = inputArray[i][j];
    }
  }
  
  // Copy the second half of the input array to outputArray2
  for (int i = midpoint; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      outputArray2[i - midpoint][j] = inputArray[i][j];
    }
  }
}
