void chessCoordsToArray(char* chessCoords, int* arrayCoords) {
  int x;
  switch(chessCoords[0]) {
    case 'A':
    case 'a':
      x = 7;
      break;
    case 'B':
    case 'b':
      x = 6;
      break;
    case 'C':
    case 'c':
      x = 5;
      break;
    case 'D':
    case 'd':
      x = 4;
      break;
    case 'E':
    case 'e':
      x = 3;
      break;
    case 'F':
    case 'f':
      x = 2;
      break;
    case 'G':
    case 'g':
      x = 1;
      break;
    case 'H':
    case 'h':
      x = 0;
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
  Serial.print("currentplayer: ");
  if (!currentplayer){
    Serial.println("white");
  }else{
    Serial.println("Black");
  }

  chessCoordsToArray(startPos, coo1);
  chessCoordsToArray(endPos, coo2);

  int originpiece = chessBoard[coo1[1]][coo1[0]];

  // check if the move is valid
  if(checkValid(originpiece, coo1, coo2)){
    swap(originpiece);
  }else{
    Serial.println("error somewhere in check");
  }
}

// move led to new position
void swap(int originpiece){
  chessBoard[coo1[1]][coo1[0]] = 0; // Remove piece from starting location
  chessBoard[coo2[1]][coo2[0]] = originpiece; // Add piece to ending location
  
  // swap player
  currentplayer = !currentplayer;
}

// checks if the piece is capturable
void checkCapture(int originpiece, int targetpiece){
  if (!currentplayer && targetpiece < 7 ){
    // currentplayer is white
    swap(originpiece);
    Serial.println("captured enemy piece");
  }else if(currentplayer && targetpiece >= 7){
    // currentplayer is black
    swap(originpiece);
    Serial.println("captured enemy piece");
  }else{
    Serial.println("can't capture your own pieces");
  }
}
