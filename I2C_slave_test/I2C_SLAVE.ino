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

// I2C receive event, gets coordinates
void receiveEvent(int bytes) {
  int arr[2]; // create an empty array to receive the data
  Wire.readBytes((byte *) &arr, sizeof(arr)); // read the data into the array
  Serial.print("Received data: ");
  Serial.print(arr[0]);
  Serial.print(", ");
  Serial.println(arr[1]);
}
