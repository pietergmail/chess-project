// boolean that checks if the move is valid
bool checkValid(int piece, int origin[2], int target[2]){
  if(currentplayer){
    // currentplayer is black
    switch(piece){
      case 1:
        if(pawncheckblack(origin, target)){
          return true;
        }else{
          return false;
        }
      case 2:
        if(rookcheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 3:
        if(knightcheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 4:
        if(bishopcheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 5:
        if(queencheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 6:
        if(kingcheck(origin, target)){
          return true;
        }else{
          return false;
        }
      default:
        Serial.println("Not one of your pieces.");
        return false;
    }
  }else{
    // currentplayer is white
    switch(piece){
      case 7:
        if(pawnCheckWhite(origin, target)){
          return true;
        }else{
          return false;
        }
      case 8:
        if(rookcheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 9:
        if(knightcheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 10:
        if(bishopcheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 11:
        if(queencheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 12:
        if(kingcheck(origin, target)){
          return true;
        }else{
          return false;
        }
      default:
        Serial.println("Not one of your pieces.");
        return false;
    }
  }
}

// Function to check if a pawn move is valid
bool pawnCheckWhite(int origin[2], int target[2]){
  int origin_y = origin[1];
  int origin_x = origin[0];

  int target_y = target[1];
  int target_x = target[0];

  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];
  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
      Serial.println("out of bounds");
      return false;
  }

  // Check if there is a pawn at the starting position
  if (originpiece != 7) {
      Serial.println(originpiece);
      Serial.println("this is not a pawn");
      return false;
  }
  // Check if the pawn is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      Serial.println("you can not move to your own position");
      return false;
  }

  // Check if the pawn is moving diagonally to capture, unfinished
  if(origin_x == target_x - 1 || origin_x == target_x + 1){
    // check if there is an enemy piece
    int enemypiece = chessBoard[target_y][target_x];
    if(enemypiece != 0 && enemypiece <= 6){
      Serial.println("sideways capture");
    }else{
      Serial.println("no enemy piece on this position");
      return false;
    }
  }

  // Check if the pawn is moving forward more than two squares
  if (origin_y ==  6 && target_y < 4) {
      Serial.println("moving forward to far");
      return false;
  }

  // check if there is piece on the current target (non capture)
  if(targetpiece != 0 && origin_x == target_x) {
      Serial.println("already a piece on this space");
      return false;
  }

  // Check if the pawn is moving forward more than one square, but there is a piece in the way
  if (origin_y == target_y + 2 && chessBoard[origin_y - 1][origin_x] != 0) {
      Serial.println("there is a piece in the way");
      return false;
  }

  // Check if the pawn is moving forward more than one square after its initial move, black
  if (origin_y != 6 && target_y < origin_y - 1){
    Serial.println("can't move two spaces after first move");
    return false;
  }

  if (origin_y < target_y){
    Serial.println("a pawn can't move backwards");
    return false;
  }
  return true;
}

bool pawncheckblack(int origin[2],int target[2]){
  int origin_y = origin[1];
  int origin_x = origin[0];

  int target_y = target[1];
  int target_x = target[0];

  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];
  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
      Serial.println("out of bounds");
      return false;
  }

  // Check if there is a pawn at the starting position
  if (originpiece != 1) {
      Serial.println(originpiece);
      Serial.println("this is not a pawn");
      return false;
  }
  // Check if the pawn is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      Serial.println("you can not move to your own position");
      return false;
  }

  // Check if the pawn is moving diagonally to capture, unfinished
  if(origin_x == target_x + 1 || origin_x == target_x - 1){
    // check if there is an enemy piece
    int enemypiece = chessBoard[target_y][target_x];
    if(enemypiece != 0 && enemypiece > 6){
      Serial.println("sideways capture");
    }else{
      Serial.println("no enemy piece on this position");
      return false;
    }
  }

  // Check if the pawn is moving forward more than two squares
  if (origin_y ==  1 && target_y > 3) {
      Serial.println("moving forward to far");
      return false;
  }

  // check if there is piece on the current target (non capture)
  if(targetpiece != 0 && origin_x == target_x) {
      Serial.println("already a piece on this space");
      return false;
  }

  // Check if the pawn is moving forward more than one square, but there is a piece in the way
  if (origin_y == target_y - 2 && chessBoard[origin_y + 1][origin_x] != 0) {
      Serial.println("there is a piece in the way");
      return false;
  }

  // Check if the pawn is moving forward more than one square after its initial move, black
  if (origin_y != 1 && target_y > origin_y + 1){
    Serial.println("can't move two spaces after first move");
    return false;
  }

  if (origin_y > target_y){
    Serial.println("a pawn can't move backwards");
    return false;
  }
  return true;
}

bool rookcheck(int origin[2],int target[2]){
  int origin_y = origin[1];
  int origin_x = origin[0];

  int target_y = target[1];
  int target_x = target[0];

  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];

  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
      Serial.println("out of bounds");
      return false;
  }

  Serial.println(originpiece);

  // Check if there is a rook at the starting position
  if (originpiece != 2 && originpiece != 8) {
      Serial.println("this is not a rook");
      return false;
  }

  // Check if the rook is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      Serial.println("you can not move to your own position");
      return false;
  }

  // Check if the rook is moving diagonally
  if(origin_x != target_x && origin_y != target_y){
    Serial.println("rooks can not move diagonally");
    return false;
  }

  // Check if there is a piece in the way of the rook's path
  if(origin_x == target_x){
    // Check if the rook is moving up or down
    int delta_y = target_y - origin_y;
    int step_y = delta_y > 0 ? 1 : -1;
    for(int i = 1; i < abs(delta_y); i++){
      if(chessBoard[origin_y + i * step_y][origin_x] != 0){
        Serial.println("there is a piece in the way");
        return false;
      }
    }
  }

  else if(origin_y == target_y){
    // Check if the rook is moving left or right
    int delta_x = target_x - origin_x;
    int step_x = delta_x > 0 ? 1 : -1;
    for(int i = 1; i < abs(delta_x); i++){
      if(chessBoard[origin_y][origin_x + i * step_x] != 0){
        Serial.println("there is a piece in the way");
        return false;
      }
    }
  }

  // Check if there is an enemy piece at the target position
  if(currentplayer){
    if(targetpiece > 6 && targetpiece <= 12){
      Serial.println("capturing enemy piece");
    }

    // Check if there is a friendly piece at the target position
    if(targetpiece > 0 && targetpiece <= 6){
      Serial.println("can not capture friendly piece");
      return false;
    }
  }else{
    if(targetpiece > 0 && targetpiece <= 6){
      Serial.println("capturing enemy piece");
    }

    // Check if there is a friendly piece at the target position
    if(targetpiece > 6 && targetpiece <= 12){
      Serial.println("can not capture friendly piece");
      return false;
    }
  }


  return true;
}

bool knightcheck(int origin[2],int target[2]){
  return true;
}

bool bishopcheck(int origin[2],int target[2]){
  return true;
}

bool queencheck(int origin[2],int target[2]){
  return true;
}

bool kingcheck(int origin[2],int target[2]){
  return true;
}