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
  if (currentplayer){
    Serial.println("white");
  }else{
    Serial.println("Black");
  }

  chessCoordsToArray(startPos, coo1);
  chessCoordsToArray(endPos, coo2);

  int originpiece = chessBoard[coo1[1]][coo1[0]];
  int targetpiece = chessBoard[coo2[1]][coo2[0]];

  // check if piece is a piece
  if(originpiece == 0){
    Serial.println("no piece on this position");
  }else{
    // check if currentpiece is of the correct player
    if(currentPiece()){
      if(targetpiece >=1){
        // there is a piece on this position
        checkCapture(originpiece, targetpiece);
      }else{
        // the target piece is empty
        swap(originpiece);
  }
    }else{
      Serial.println("That's one of the oponent's pieces");
    }
  }
}

// check if currentpiece is correct for current player
bool currentPiece(int originpiece){
  if (!currentplayer && targetpiece >= 7 ){
    // currentplayer is white
    return true;
  }else if(currentplayer && targetpiece < 7){
    // currentplayer is black
    return true;
  }else{
    return false;
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
