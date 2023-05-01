void chessCoordsToArray(char* chessCoords, int* arrayCoords) {
  int x;
  switch(chessCoords[0]) {
    case 'A':
    case 'a':
      x = 0;
      break;
    case 'B':
    case 'b':
      x = 1;
      break;
    case 'C':
    case 'c':
      x = 2;
      break;
    case 'D':
    case 'd':
      x = 3;
      break;
    case 'E':
    case 'e':
      x = 4;
      break;
    case 'F':
    case 'f':
      x = 5;
      break;
    case 'G':
    case 'g':
      x = 6;
      break;
    case 'H':
    case 'h':
      x = 7;
      break;
    default:
      x = -1; // invalid, will crash
      break;
  }

  // convert char to int, then mirror it
  int y = 8 - (chessCoords[1] - '0');

  arrayCoords[0] = x;
  arrayCoords[1] = y;
}

// moves the piece to the new location
void movePiece(char startPos[], char endPos[]) {
  chessCoordsToArray(startPos, coo1);
  chessCoordsToArray(endPos, coo2);

  int piece = chessBoard[coo1[1]][coo1[0]];
  Serial.println(coo1[0]);
  Serial.println(coo1[1]);
  
  // empties out weirdly, actually does nothing???
  chessBoard[coo1[1]][coo1[0]] = 0; // Remove piece from starting location
  // is not added????
  chessBoard[coo2[1]][coo2[0]] = piece; // Add piece to ending location

    for (int i = 0; i < 8; i++) {
  // Iterate through the columns
    for (int j = 0; j < 8; j++) {
      // Print the element at the current row and column
      Serial.print(chessBoard[i][j]);
      Serial.print("\t"); // Add a tab between elements for better readability
    }
  Serial.println(); // Move to the next line after each row
  }
}
