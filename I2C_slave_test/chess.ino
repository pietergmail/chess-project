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
  
  int origin_y = coo1[1];
  int origin_x = coo1[0];
  
  int target_y = coo2[1];
  int target_x = coo2[0];

  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];

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

  if (currentplayer){
    // check if the move is valid black
    if(blackCheckValid(originpiece, origin_x, origin_y, target_x, target_y)){
      
      // set casteling
      castelingflag(originpiece, origin_x, origin_y, target_x, target_y);

      swap(originpiece, origin_x, origin_y, target_x, target_y);
      // swap to the next player
      currentplayer = !currentplayer;
      // check if a pawn has reached the end of the board
      if(originpiece == 1){
        promotioncheck();
      }
    }
  }else{
    // check if the move is valid white
    if(whiteCheckValid(originpiece, origin_x, origin_y, target_x, target_y)){

      // set casteling
      castelingflag(originpiece, origin_x, origin_y, target_x, target_y);

      swap(originpiece, origin_x, origin_y, target_x, target_y);
      // swap to the next player
      currentplayer = !currentplayer;
      // check if a pawn has reached the end of the board
      if(originpiece == 7){
        promotioncheck();
      }
    }
  }
}

// move led to new position
void swap(int originpiece, int origin_x, int origin_y, int target_x, int target_y){
  chessBoard[origin_y][origin_x] = 0; // Remove piece from starting location
  chessBoard[target_y][target_x] = originpiece; // Add piece to ending location
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

void castelingflag(int currentpiece, int origin_x, int origin_y, int target_x, int target_y){
  if(currentpiece == 2){
    // check which rook
    if(origin_x == 7){
      casteling_black[0] = false;
    }else{
      casteling_black[2] = false;
    }
  }else if(currentpiece == 8){
    // check which rook
    if(origin_x == 7){
      casteling_white[0] = false;
    }else{
      casteling_white[2] = false;
    }
  }else if(currentpiece == 6){
    casteling_black[1] = false;
  }else if(currentpiece == 12){
    casteling_white[1] = false;
  }
}

void gameEnd(){
  Serial.println("MATE");
}

