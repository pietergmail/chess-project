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
        if(knightCheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 4:
        if(bishopCheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 5:
        if(queenCheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 6:
        if(kingCheck(origin, target)){
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
        if(knightCheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 10:
        if(bishopCheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 11:
        if(queenCheck(origin, target)){
          return true;
        }else{
          return false;
        }
      case 12:
        if(kingCheck(origin, target)){
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

// Function to check if a knight move is valid
bool knightCheck(int origin[2], int target[2]) {
  int origin_x = origin[0];
  int origin_y = origin[1];
  int target_x = target[0];
  int target_y = target[1];

  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];

  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
    Serial.println("Out of bounds.");
    return false;
  }

  if(originpiece != 3 && originpiece != 9){
    Serial.println("not a horesy.");
    return false;
  }

  int dx = abs(target_x - origin_x);
  int dy = abs(target_y - origin_y);

  // Check if the move is a valid L-shape (2 squares in one direction, 1 square in the other)
  if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
    Serial.println("Invalid move for knight.");
    return false;
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

// Function to check if a bishop move is valid
bool bishopCheck(int origin[2], int target[2]) {
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
  
  // Check if there is a bishop at the starting position
  if (originpiece != 4 && originpiece != 10) {
    Serial.println("this is not a bishop");
    return false;
  }
  
  // Check if the bishop is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
    Serial.println("you can not move to your own position");
    return false;
  }
  
  // Check if the bishop is moving diagonally, not sure about this
  if (abs(origin_x - target_x) != abs(origin_y - target_y)) {
    Serial.println("this move is not diagonal");
    return false;
  }
  
  // Check if there are any pieces in the bishop's path
  int x_dir = (target_x - origin_x) > 0 ? 1 : -1;
  int y_dir = (target_y - origin_y) > 0 ? 1 : -1;
  
  int current_x = origin_x + x_dir;
  int current_y = origin_y + y_dir;
  
  while (current_x != target_x && current_y != target_y) {
    if (chessBoard[current_y][current_x] != 0) {
      Serial.println("there is a piece in the way");
      return false;
    }
    current_x += x_dir;
    current_y += y_dir;
  }
  
  // Check if the bishop is capturing an enemy piece
  if (targetpiece != 0) {
    if (currentplayer && targetpiece >= 7 && targetpiece <= 12) {
      Serial.println("capturing an enemy piece");
      return true;
    }
    if (!currentplayer && originpiece <= 12 && targetpiece < 7) {
      Serial.println("capturing an enemy piece");
      return true;
    }
    Serial.println("can not capture your own piece");
    return false;
  }
  
  // The move is valid if there are no pieces in the bishop's path and the target square is empty
  return true;
}

// Function to check if a queen move is valid
bool queenCheck(int origin[2], int target[2]){
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

  // Check if the queen is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      Serial.println("you can not move to your own position");
      return false;
  }

  // Check if the queen is moving horizontally or vertically
  if (origin_x != target_x && origin_y != target_y) {
      // Check if the queen is moving diagonally
      if (abs(target_x - origin_x) != abs(target_y - origin_y)) {
          Serial.println("invalid move for queen");
          return false;
      }
  }

  // Check if there is a piece in the way of the queen's movement
  if (origin_x == target_x) {
      // Vertical movement
      int direction = (target_y - origin_y) / abs(target_y - origin_y);
      for (int i = origin_y + direction; i != target_y; i += direction) {
          if (chessBoard[i][origin_x] != 0) {
              Serial.println("there is a piece in the way");
              return false;
          }
      }
  } else if (origin_y == target_y) {
      // Horizontal movement
      int direction = (target_x - origin_x) / abs(target_x - origin_x);
      for (int i = origin_x + direction; i != target_x; i += direction) {
          if (chessBoard[origin_y][i] != 0) {
              Serial.println("there is a piece in the way");
              return false;
          }
      }
  } else {
      // Diagonal movement
      int x_direction = (target_x - origin_x) / abs(target_x - origin_x);
      int y_direction = (target_y - origin_y) / abs(target_y - origin_y);
      for (int i = 1; i < abs(target_x - origin_x); i++) {
          if (chessBoard[origin_y + i*y_direction][origin_x + i*x_direction] != 0) {
              Serial.println("there is a piece in the way");
              return false;
          }
      }
  }

  // Check if the queen is capturing an enemy piece
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

// Function to check if a king move is valid
bool kingCheck(int origin[2], int target[2]){
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

  // Check if there is a king at the starting position
  if (originpiece != 12 && originpiece != 6) {
      Serial.println("this is not a king");
      return false;
  }

  // Check if the king is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      Serial.println("you can not move to your own position");
      return false;
  }

  // Check if the king  is capturing an enemy piece
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

  // Check if the king is moving to a neighboring square
  if (abs(target_x - origin_x) <= 1 && abs(target_y - origin_y) <= 1) {
      // Check if the target square contains an enemy piece

      // Check if the king is too close to the other king
      int otherKingX;
      int otherKingY;

      // check black 
      if(currentplayer){
        for (int y = 0; y < 8; y++) {
          for (int x = 0; x < 8; x++) {
            if (chessBoard[y][x] == 12) {
              otherKingX = x;
              otherKingY = y;
            }
          }
        }
      }else{
        for (int y = 0; y < 8; y++) {
          for (int x = 0; x < 8; x++) {
            if (chessBoard[y][x] == 6) {
              otherKingX = x;
              otherKingY = y;
            }
          }
        }
      }

      // check if kings to close
      if (abs(otherKingX - target_x) <= 1 && abs(otherKingY - target_y) <= 1) {
          Serial.println("two kings can't get too close to each other");
          return false;
      }

      return true;
  }

  // Invalid move
  Serial.println("invalid move for a king");
  return false;
}