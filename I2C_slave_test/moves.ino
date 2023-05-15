// boolean that checks if the move is valid
bool blackCheckValid(int piece, int origin_x, int origin_y, int target_x, int target_y){
  switch(piece){
    case 1:
      if(pawncheckblack(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 2:
      if(rookcheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 3:
      if(knightCheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 4:
      if(bishopCheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 5:
      if(queenCheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 6:
      if(kingCheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    default:
      lcdString=("Not one of your pieces.");
      return false;
  }
  // declare and initialize the boardTemp array
  int boardTemp[8][8];

  // copy the values from chessBoard to boardTemp
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      boardTemp[i][j] = chessBoard[i][j];
    }
  }

  // make new move
  swap(piece, origin_x, origin_y, target_x, target_y);
  // check if new move puts you in check
  if(checkBlack()){
    lcdString=("New move puts you in check.");
    // swap back the old board
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        chessBoard[i][j] = boardTemp[i][j];
      }
    }
    return false;
  }else{
    // swap back the old board
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        chessBoard[i][j] = boardTemp[i][j];
      }
    }
    return true;
  }
}

bool whiteCheckValid(int piece, int origin_x, int origin_y, int target_x, int target_y){
  // currentplayer is white
  switch(piece){
    case 7:
      if(pawnCheckWhite(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 8:
      if(rookcheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 9:
      if(knightCheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 10:
      if(bishopCheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 11:
      if(queenCheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    case 12:
      if(kingCheck(origin_x, origin_y, target_x, target_y)){
        break;
      }else{
        return false;
      }
    default:
      lcdString=("Not one of your pieces.");
      return false;
  }
  // declare and initialize the boardTemp array
  int boardTemp[8][8];

  // copy the values from chessBoard to boardTemp
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      boardTemp[i][j] = chessBoard[i][j];
    }
  }

  // make new move
  swap(piece, origin_x, origin_y, target_x, target_y);
  // check if new move puts you in check
  if(checkWhite()){
    lcdString=("New puts keeps you in check.");
    // swap back the old board
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        chessBoard[i][j] = boardTemp[i][j];
      }
    }
    return false;
  }else{
    // swap back the old board
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        chessBoard[i][j] = boardTemp[i][j];
      }
    }
    return true;
  }
}

// Function to check if a pawn move is valid
bool pawnCheckWhite(int origin_x, int origin_y, int target_x, int target_y){
  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];
  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
      lcdString=("out of bounds");
      return false;
  }

  // Check if there is a pawn at the starting position
  if (originpiece != 7) {
      lcdString=(originpiece);
      lcdString=("this is not a pawn");
      return false;
  }
  // Check if the pawn is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      lcdString=("you can not move to your own position");
      return false;
  }

  // Check if the pawn is moving diagonally to capture, unfinished
  if(origin_x == target_x - 1 || origin_x == target_x + 1){
    // check if there is an enemy piece
    int enemypiece = chessBoard[target_y][target_x];
    if(enemypiece != 0 && enemypiece <= 6){
      lcdString=("sideways capture");
    }else if(en_passent[0] == target_x && en_passent[1] == target_y){
      // empty out attacked piece
      chessBoard[target_y + 1][target_x] = 0;

      lcdString=("EN PASSENT");
    }else{
      lcdString=("no enemy piece on this position");
      return false;
    }
  }

  // Check if the pawn is moving forward more than two squares
  if (origin_y ==  6 && target_y < 4) {
      lcdString=("moving forward to far");
      return false;
  }

  // check if there is piece on the current target (non capture)
  if(targetpiece != 0 && origin_x == target_x) {
      lcdString=("already a piece on this space");
      return false;
  }

  // Check if the pawn is moving forward more than one square, but there is a piece in the way
  if (origin_y == target_y + 2 && chessBoard[origin_y - 1][origin_x] != 0) {
      lcdString=("there is a piece in the way");
      return false;
  }

  // Check if the pawn is moving forward more than one square after its initial move, black
  if (origin_y != 6 && target_y < origin_y - 1){
    lcdString=("can't move two spaces after first move");
    return false;
  }

  if (origin_y < target_y){
    lcdString=("a pawn can't move backwards");
    return false;
  }

  // check if movement 2, en passent time
  if(abs(origin_y - target_y) == 2){
    en_passent[0] = origin_x;
    en_passent[1] = origin_y - 1;
    en_passent[2] = 1;
  }

  return true;
}

bool pawncheckblack(int origin_x, int origin_y, int target_x, int target_y){
  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];
  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
      lcdString=("out of bounds");
      return false;
  }

  // Check if there is a pawn at the starting position
  if (originpiece != 1) {
      lcdString=(originpiece);
      lcdString=("this is not a pawn");
      return false;
  }
  // Check if the pawn is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      lcdString=("you can not move to your own position");
      return false;
  }

  // Check if the pawn is moving diagonally to capture, unfinished
  if(origin_x == target_x + 1 || origin_x == target_x - 1){
    // check if there is an enemy piece
    int enemypiece = chessBoard[target_y][target_x];
    if(enemypiece != 0 && enemypiece > 6){
      lcdString=("sideways capture");
    }else if(en_passent[0] == target_x && en_passent[1] == target_y){
      // empty out attacked piece
      chessBoard[target_y - 1][target_x] = 0;

      lcdString=("EN PASSENT");
    }else{
      lcdString=("no enemy piece on this position");
      return false;
    }
  }

  // Check if the pawn is moving forward more than two squares
  if (origin_y ==  1 && target_y > 3) {
      lcdString=("moving forward to far");
      return false;
  }

  // check if there is piece on the current target (non capture)
  if(targetpiece != 0 && origin_x == target_x) {
      lcdString=("already a piece on this space");
      return false;
  }

  // Check if the pawn is moving forward more than one square, but there is a piece in the way
  if (origin_y == target_y - 2 && chessBoard[origin_y + 1][origin_x] != 0) {
      lcdString=("there is a piece in the way");
      return false;
  }

  // Check if the pawn is moving forward more than one square after its initial move, black
  if (origin_y != 1 && target_y > origin_y + 1){
    lcdString=("can't move two spaces after first move");
    return false;
  }

  if (origin_y > target_y){
    lcdString=("a pawn can't move backwards");
    return false;
  }

  // check if movement 2, en passent time
  if(abs(origin_y - target_y) == 2){
    en_passent[0] = origin_x;
    en_passent[1] = origin_y + 1;
    en_passent[2] = 2;
  }

  return true;
}

bool rookcheck(int origin_x, int origin_y, int target_x, int target_y){
  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];

  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
      lcdString=("out of bounds");
      return false;
  }

  lcdString=(originpiece);

  // Check if there is a rook at the starting position
  if (originpiece != 2 && originpiece != 8) {
      lcdString=("this is not a rook");
      return false;
  }

  // Check if the rook is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      lcdString=("you can not move to your own position");
      return false;
  }

  // Check if the rook is moving diagonally
  if(origin_x != target_x && origin_y != target_y){
    lcdString=("rooks can not move diagonally");
    return false;
  }

  // Check if there is a piece in the way of the rook's path
  if(origin_x == target_x){
    // Check if the rook is moving up or down
    int delta_y = target_y - origin_y;
    int step_y = delta_y > 0 ? 1 : -1;
    for(int i = 1; i < abs(delta_y); i++){
      if(chessBoard[origin_y + i * step_y][origin_x] != 0){
        lcdString=("there is a piece in the way");
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
        lcdString=("there is a piece in the way");
        return false;
      }
    }
  }

  // Check if there is an enemy piece at the target position
  if(currentplayer){
    if(targetpiece > 6 && targetpiece <= 12){
      lcdString="capturing enemy piece";
    }

    // Check if there is a friendly piece at the target position
    if(targetpiece > 0 && targetpiece <= 6){
      lcdString="can not capture friendly piece";
      return false;
    }
  }else{
    if(targetpiece > 0 && targetpiece <= 6){
      lcdString="capturing enemy piece";
    }

    // Check if there is a friendly piece at the target position
    if(targetpiece > 6 && targetpiece <= 12){
      lcdString="can not capture friendly piece";
      return false;
    }
  }

  return true;
}

// Function to check if a knight move is valid
bool knightCheck(int origin_x, int origin_y, int target_x, int target_y) {
  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];

  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
    lcdString="Out of bounds.";
    return false;
  }

  if(originpiece != 3 && originpiece != 9){
    lcdString="not a horesy.";
    return false;
  }

  int dx = abs(target_x - origin_x);
  int dy = abs(target_y - origin_y);

  // Check if the move is a valid L-shape (2 squares in one direction, 1 square in the other)
  if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
    lcdString="Invalid move for knight.";
    return false;
  }

  // Check if there is an enemy piece at the target position
  if(currentplayer){
    if(targetpiece > 6 && targetpiece <= 12){
      lcdString="capturing enemy piece";
    }

    // Check if there is a friendly piece at the target position
    if(targetpiece > 0 && targetpiece <= 6){
      lcdString="can not capture friendly piece";
      return false;
    }
  }else{
    if(targetpiece > 0 && targetpiece <= 6){
      lcdString="capturing enemy piece";
    }

    // Check if there is a friendly piece at the target position
    if(targetpiece > 6 && targetpiece <= 12){
      lcdString="can not capture friendly piece";
      return false;
    }
  }

  return true;
}

// Function to check if a bishop move is valid
bool bishopCheck(int origin_x, int origin_y, int target_x, int target_y) {
  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];
  
  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
    lcdString="out of bounds";
    return false;
  }
  
  // Check if there is a bishop at the starting position
  if (originpiece != 4 && originpiece != 10) {
    lcdString="this is not a bishop";
    return false;
  }
  
  // Check if the bishop is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
    lcdString="you can not move to your own position";
    return false;
  }
  
  // Check if the bishop is moving diagonally, not sure about this
  if (abs(origin_x - target_x) != abs(origin_y - target_y)) {
    lcdString="this move is not diagonal";
    return false;
  }
  
  // Check if there are any pieces in the bishop's path
  int x_dir = (target_x - origin_x) > 0 ? 1 : -1;
  int y_dir = (target_y - origin_y) > 0 ? 1 : -1;
  
  int current_x = origin_x + x_dir;
  int current_y = origin_y + y_dir;
  
  while (current_x != target_x && current_y != target_y) {
    if (chessBoard[current_y][current_x] != 0) {
      lcdString="there is a piece in the way";
      return false;
    }
    current_x += x_dir;
    current_y += y_dir;
  }
  
  // Check if the bishop is capturing an enemy piece
  if (targetpiece != 0) {
    if (currentplayer && targetpiece >= 7 && targetpiece <= 12) {
      lcdString="capturing an enemy piece";
      return true;
    }
    if (!currentplayer && originpiece <= 12 && targetpiece < 7) {
      lcdString="capturing an enemy piece";
      return true;
    }
    lcdString="can not capture your own piece";
    return false;
  }
  
  // The move is valid if there are no pieces in the bishop's path and the target square is empty
  return true;
}

// Function to check if a queen move is valid
bool queenCheck(int origin_x, int origin_y, int target_x, int target_y){
  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];

  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
      lcdString="out of bounds";
      return false;
  }

  // Check if the queen is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      lcdString="you can not move to your own position";
      return false;
  }

  // Check if the queen is moving horizontally or vertically
  if (origin_x != target_x && origin_y != target_y) {
      // Check if the queen is moving diagonally
      if (abs(target_x - origin_x) != abs(target_y - origin_y)) {
          lcdString="invalid move for queen";
          return false;
      }
  }

  // Check if there is a piece in the way of the queen's movement
  if (origin_x == target_x) {
      // Vertical movement
      int direction = (target_y - origin_y) / abs(target_y - origin_y);
      for (int i = origin_y + direction; i != target_y; i += direction) {
          if (chessBoard[i][origin_x] != 0) {
              lcdString="there is a piece in the way";
              return false;
          }
      }
  } else if (origin_y == target_y) {
      // Horizontal movement
      int direction = (target_x - origin_x) / abs(target_x - origin_x);
      for (int i = origin_x + direction; i != target_x; i += direction) {
          if (chessBoard[origin_y][i] != 0) {
              lcdString="there is a piece in the way";
              return false;
          }
      }
  } else {
      // Diagonal movement
      int x_direction = (target_x - origin_x) / abs(target_x - origin_x);
      int y_direction = (target_y - origin_y) / abs(target_y - origin_y);
      for (int i = 1; i < abs(target_x - origin_x); i++) {
          if (chessBoard[origin_y + i*y_direction][origin_x + i*x_direction] != 0) {
              lcdString="there is a piece in the way";
              return false;
          }
      }
  }

  // Check if the queen is capturing an enemy piece
  if(currentplayer){
    // Check if there is a friendly piece at the target position
    if(targetpiece > 0 && targetpiece <= 6){
      lcdString="can not capture friendly piece";
      return false;
    }
  }else{
    // Check if there is a friendly piece at the target position
    if(targetpiece > 6 && targetpiece <= 12){
      lcdString="can not capture friendly piece";
      return false;
    }
  }

  return true;
}

// Function to check if a king move is valid
bool kingCheck(int origin_x, int origin_y, int target_x, int target_y){
  int originpiece = chessBoard[origin_y][origin_x];
  int targetpiece = chessBoard[target_y][target_x];

  // Check if the starting and ending positions are within the bounds of the board
  if (origin_x < 0 || origin_x > 7 || origin_y < 0 || origin_y > 7 || target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) {
      lcdString="out of bounds";
      return false;
  }

  // Check if there is a king at the starting position
  if (originpiece != 12 && originpiece != 6) {
      lcdString="this is not a king";
      return false;
  }

  // Check if the king is moving to its own position
  if (origin_x == target_x && origin_y == target_y) {
      lcdString="you can not move to your own position";
      return false;
  }

  // Check if the king  is capturing an enemy piece
  if(currentplayer){
    if(targetpiece > 6 && targetpiece <= 12){
      lcdString="capturing enemy piece";
    }

    // Check if there is a friendly piece at the target position
    if(targetpiece > 0 && targetpiece <= 6){
      lcdString="can not capture friendly piece";
      return false;
    }
  }else{
    if(targetpiece > 0 && targetpiece <= 6){
      lcdString="capturing enemy piece";
    }

    // Check if there is a friendly piece at the target position
    if(targetpiece > 6 && targetpiece <= 12){
      lcdString="Can't capture your own pieces";
      return false;
    }
  }

  // casteling check
  // white
  if(!currentplayer){
    // check if the user wants to castle
    if(target_y == 7 && target_x == 5 && origin_y == 7 && origin_x == 3){
      if(!inCheck){
      // check if casteling is still allowed
        if(casteling_white[0] && casteling_white[1]){
          // check if there is space
          if(chessBoard[7][4] == 0 && chessBoard[7][5] == 0 && chessBoard[7][6] == 0){
            // check if other king in the way
            if(KingCloseCheck(target_x, target_y)){
              // set casteling flags
              casteling_white[1] = false;
              casteling_white[2] = false;
              //move the rook
              int rook_origin[2] = {7, 7};
              int rook_target[2] = {4, 7};
              swap(8, 7, 7, 4, 7);
              // check is finished
              lcdString="casteling epic.";
              return true;
            }else{
              lcdString="Other pieces in the way";
              return false;
            }
          }else{
            lcdString="there are pieces in the way";
            return false;
          }
        }else{
          lcdString="casteling no longer allowed like that";
          return false;
        }
      }else{
        lcdString="Can't castle while in check";
        return false;
    }
    // check for other casteling option
    }else if(target_y == 7 && target_x == 1 && origin_y == 7 && origin_x == 3){
      if(!inCheck){
        // check if casteling is still allowed
        if(casteling_white[1] && casteling_white[2]){
          // check if there is space
          if(chessBoard[7][1] == 0 && chessBoard[7][2] == 0){
            // check if other king in the way
            if(KingCloseCheck(target_x, target_y)){
              // set casteling flags
              casteling_white[1] = false;
              casteling_white[2] = false;
              //move the rook
              swap(8, 0, 7, 2, 7);
              // check is finished
              lcdString="casteling epic";
              return true;
            }else{
              lcdString="Other pieces in the way";
              return false;
            }
          }else{
            lcdString="there are pieces in the way";
            return false;
          }
        }else{
          lcdString="casteling no longer allowed like that.";
          return false;
        }
      }else{
          lcdString="Can't castle while in check";
          return false;
      }
    }
  //black
  }else{  
    // check if the user wants to castle
    if(target_y == 0 && target_x == 5 && origin_y == 0 && origin_x == 3){
      if(!inCheck){
        // check if casteling is still allowed
        if(casteling_black[0] && casteling_black[1]){
          // check if there is space
          if(chessBoard[0][4] == 0 && chessBoard[0][5] == 0 && chessBoard[0][6] == 0){
            // check if other king in the way
            if(KingCloseCheck(target_x, target_y)){
              // set casteling flags
              casteling_black[1] = false;
              casteling_black[0] = false;
              //move the rook
              swap(2, 7, 0, 4, 0);
              // check is finished
              lcdString="casteling epic!";
              return true;
            }else{
              lcdString="Other pieces in the way";
              return false;
            }
          }else{
            lcdString = "there are pieces in the way";
            return false;
          }
        }else{
          lcdString = "casteling no longer allowed like that.";
          return false;
        }
      }else{
        lcdString = "Can't castle while in check";
        return false;
      }
    // check for other casteling option
    }else if(target_y == 0 && target_x == 1 && origin_y == 0 && origin_x == 3){
      if(!inCheck){
        // check if casteling is still allowed
        if(casteling_black[1] && casteling_black[2]){
          // check if there is space
          if(chessBoard[0][1] == 0 && chessBoard[0][2] == 0){
            // check if other king in the way
            if(KingCloseCheck(target_x, target_y)){
              // set casteling flags
              casteling_black[1] = false;
              casteling_black[2] = false;
              // move the rook
              swap(2, 0, 0, 2, 0);
              // check is finished
              lcdString=("casteling epic.");
              return true;
            }else{
              lcdString=("Other pieces in the way");
              return false;
            }
          }else{
            lcdString=("there are pieces in the way");
            return false;
          }
        }else{
          lcdString=("casteling no longer allowed like that.");
          return false;
        }
      }else{
        lcdString=("Can not castle while in check");
        return false;
      }      
    }
  }

  // Check if the king is moving to a neighboring square
  if (abs(target_x - origin_x) <= 1 && abs(target_y - origin_y) <= 1) {
      // Check if the target square contains an enemy piece

    if(KingCloseCheck(target_x, target_y)){
      return true;
    }
  }

  // Invalid move
  lcdString = "invalid move for a king";
  return false;
}

bool KingCloseCheck(int target_x, int target_y){
  // Check if the king is too close to the other king
  int otherKingX;
  int otherKingY;

  if(currentplayer){
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (chessBoard[y][x] == 12) {
        otherKingX = x;
        otherKingY = y;
      }
    }
  }
  // check white
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
      lcdString = "two kings can't get too close to each other";
      return false;
  }

  return true;
}
