// I2C request event callback function
void requestEvent() {
  // Send the appropriate array over I2C
  if (currentArray == 1) {
    Serial.println("sending array 1");
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 8; j++) {
        Wire.write(myArray1[i][j]);
      }
    }
    currentArray = 2; // Set the flag variable to 2 for the next time
  }
  else {
    Serial.println("sending array 2");
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 8; j++) {
        Wire.write(myArray2[i][j]);
      }
    }
    currentArray = 1; // Set the flag variable to 1 for the next time
  }
}

// I2C receive event, gets coordinates
void receiveEvent(int bytes) {
  if (useArr1) {
    // read the data into arr1
    Wire.readBytes(arr1, sizeof(arr1));
    Serial.print("Received data into arr1: ");
    Serial.print(arr1[0]);
    Serial.print(", ");
    Serial.println(arr1[1]);
  }
  else {
    // read the data into arr2
    Wire.readBytes(arr2, sizeof(arr2));
    Serial.print("Received data into arr2: ");
    Serial.print(arr2[0]);
    Serial.print(", ");
    Serial.println(arr2[1]);
    generateArray();
  }
  
  // toggle the useArr1 flag
  useArr1 = !useArr1;
}
