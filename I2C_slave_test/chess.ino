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

    // en passent removal
  if(en_passent[2] == 1 && !currentplayer){
    // assign them to unreachable numbers
    en_passent[0] = 10;
    en_passent[1] = 10;
    en_passent[2] = 0;
  }else if(en_passent[2] == 2 && currentplayer){
    // assign them to unreachable numbers
    en_passent[0] = 10;
    en_passent[1] = 10;
    en_passent[2] = 0;
  }

  // check if the move is valid
  if(checkValid(originpiece, coo1, coo2)){
    swap(originpiece, coo1, coo2);
    // check if a pawn has reached the end of the board
    if(originpiece == 1 || originpiece == 7){
      promotioncheck();
    }
  }else{
    Serial.println("error somewhere in check");
  }
}

// move led to new position
void swap(int originpiece, int origin[2], int target[2]){
  chessBoard[origin[1]][origin[0]] = 0; // Remove piece from starting location
  chessBoard[target[1]][target[0]] = originpiece; // Add piece to ending location
  
  // swap player
  currentplayer = !currentplayer;
}

void promotioncheck(){
   // Check if there is a black pawn on the first row
  for (int i = 0; i < 8; i++) {
      if (chessBoard[0][i] == 7) {
        // change pawn to queen
        chessBoard[0][i] = 11;
        // there can only be one promotion, return
        return;
      }
  }

  // Check if there is a white pawn on the last row
  for (int i = 0; i < 8; i++) {
      if (chessBoard[7][i] == 1) {
        // change pawn to queen
        chessBoard[7][i] = 5;
        // there can only be one promotion, return
        return;
    }
  }
}

