// not full logic, save on compute
bool checkBlack(){
  // give initial values to avoid errors
  int king_y = 10;
  int king_x = 10;

  // currentplayer is black
  // search for the king
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(chessBoard[i][j] == 6) {
        king_y = i;
        king_x = j;
      }
    }
  }

  // check front left pawn
  if (king_x - 1 >= 0 && king_y + 1 >= 0 && king_x - 1 <= 7 && king_y + 1 <= 7) {
    if (chessBoard[king_y + 1][king_x - 1] == 7) {
      // a white pawn is to the front-left of the black king
      lcdString=("currently in check front left pawn");
      return true;
    }
  }

  // check front right pawn
  if (king_x + 1 >= 0 && king_y + 1 >= 0 && king_x + 1 <= 7 && king_y + 1 <= 7) {
    if (chessBoard[king_y + 1][king_x + 1] == 7) {
      // a white pawn is to the front-right of the black king
      lcdString=("currently in check front right pawn");
      return true;
    }
  }


  // check if there is a rook or queen horizontally/vertically
  // Check row
  // swap player
  currentplayer = !currentplayer;
  for(int i = 0; i < 8; i++) {
    if(chessBoard[king_y][i] == 8 || chessBoard[king_y][i] == 11) {
      int currentpiece = chessBoard[king_y][i];
      // check if the rook can capture
      if(currentpiece == 8){
        // check if the rook can capture
        if(whiteCheckValid(8, i, king_y, king_x, king_y)){
          // a white tower is on the same line as the black king
          lcdString=("currently in check rook horizontal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if(currentpiece == 11){
        // check if the queen can capture
        if(whiteCheckValid(11, i, king_y, king_x, king_y)){
          // a white queen is on the same line as the king
          lcdString=("currently in check queen horizontal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
  }

  // Check column
  for(int i = 0; i < 8; i++) {
    if(chessBoard[i][king_x] == 8 || chessBoard[i][king_x] == 11) {
      int currentpiece = chessBoard[i][king_x];
      // check if the rook can capture
      if(currentpiece == 8){
        // check if the rook can capture
        if(whiteCheckValid(8, king_x, i, king_x, king_y)){
          // a white tower is on the same line as the black king
          lcdString=("currently in check rook vertical");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if(currentpiece == 11){
        // check if the queen can capture
        if(whiteCheckValid(11, king_x, i, king_x, king_y)){
          // a white queen is on the same line as the black king
          lcdString=("currently in check queen vertical");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
  }

  // Check diagonal (top-left to bottom-right)
  int x = king_x;
  int y = king_y;
  while (x >= 0 && y >= 0) {
    if (chessBoard[y][x] == 10 || chessBoard[y][x] == 11) {
      int currentpiece = chessBoard[y][x];
      // check if the bishop can capture
        if (currentpiece == 10) {
          if (whiteCheckValid(10, x, y, king_x, king_y)) {
            // a white bishop is on the same diagonal as the black king
            lcdString=("currently in check rook diagonal");
            // swap player back
            currentplayer = !currentplayer;
            return true;
          }
        }else if (currentpiece == 11) {
          if (whiteCheckValid(11, x, y, king_x, king_y)) {
            // a white queen is on the same diagonal as the black king
            lcdString=("currently in check queen diagonal");
            // swap player back
            currentplayer = !currentplayer;
            return true;
          }
        }
      }
      x--;
      y--;
  }

  // Check diagonal (top-right to bottom-left)
  x = king_x;
  y = king_y;
  while (x < 8 && y >= 0) {
    if (chessBoard[y][x] == 10 || chessBoard[y][x] == 11) {
      int currentpiece = chessBoard[y][x];
      // check if the bishop can capture
      if (currentpiece == 10) {
        if (whiteCheckValid(10, x, y, king_x, king_y)) {
          // a white bishop is on the same diagonal as the black king
          lcdString=("currently in check bishop diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if (currentpiece == 11) {
        if (whiteCheckValid(11, x, y, king_x, king_y)) {
          // a white queen is on the same diagonal as the black king
          lcdString=("currently in check queen diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
    x++;
    y--;
  }

  // Check diagonal (bottom-left to top-right)
  x = king_x;
  y = king_y;
  while (x < 8 && y < 8) {
    if (chessBoard[y][x] == 10 || chessBoard[y][x] == 11) {
      int currentpiece = chessBoard[y][x];
      // check if the bishop can capture
      if (currentpiece == 10) {
        if (whiteCheckValid(10, x, y, king_x, king_y)) {
          // a white bishop is on the same diagonal as the black king
          lcdString=("currently in check bishop diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if (currentpiece == 11) {
        if (whiteCheckValid(11, x, y, king_x, king_y)) {
          // a white queen is on the same diagonal as the black king
          lcdString=("currently in check queen diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
    x++;
    y++;
  }

  // Check diagonal (bottom-right to top-left)
  x = king_x;
  y = king_y;
  while (x >= 0 && y < 8) {
    if (chessBoard[y][x] == 10 || chessBoard[y][x] == 11) {
      int currentpiece = chessBoard[y][x];
      // check if the bishop can capture
      if (currentpiece == 10) {
        if (whiteCheckValid(10, x, y, king_x, king_y)) {
          // a white bishop is on the same diagonal as the black king
          lcdString=("currently in check bishop diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if (currentpiece == 11) {
        if (whiteCheckValid(11, x, y, king_x, king_y)) {
          // a white queen is on the same diagonal as the black king
          lcdString=("currently in check queen diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
    x--;
    y++;
  }

  // check if knight can attack
  int knight_moves_x[] = {2, 1, -1, -2, -2, -1, 1, 2};
  int knight_moves_y[] = {1, 2, 2, 1, -1, -2, -2, -1};

  for (int i = 0; i < 8; i++) {
    int knight_x = king_x + knight_moves_x[i];
    int knight_y = king_y + knight_moves_y[i];
    if (knight_x >= 0 && knight_x <= 7 && knight_y >= 0 && knight_y <= 7) {
      if (chessBoard[knight_y][knight_x] == 9) {
        // an opposing knight is attacking the black king
        lcdString=("currently in check by horsey");
        // swap player back
        currentplayer = !currentplayer;
        return true;
      }
    }
  }

  // no cheque found
  currentplayer = !currentplayer;
  return false;
}

bool checkWhite(){
  // give initial values to avoid errors
  int king_y = 10;
  int king_x = 10;

  // currentplayer is black
  // search for the king
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(chessBoard[i][j] == 12) {
        king_y = i;
        king_x = j;
      }
    }
  }

  // check front left pawn
  if (king_x - 1 >= 0 && king_y - 1 >= 0 && king_x - 1 <= 7 && king_y - 1 <= 7) {
    if (chessBoard[king_y - 1][king_x - 1] == 1) {
      // a white pawn is to the front-left of the black king
      lcdString=("currently in check front right pawn");
      return true;
    }
  }

  // check front right pawn
  if (king_x + 1 >= 0 && king_y - 1 >= 0 && king_x + 1 <= 7 && king_y - 1 <= 7) {
    if (chessBoard[king_y - 1][king_x + 1] == 1) {
      // a white pawn is to the front-right of the black king
      lcdString=("currently in check front left pawn");
      return true;
    }
  }


  // check if there is a rook or queen horizontally/vertically
  // Check row
  // swap player temporarely
  currentplayer = !currentplayer;
  for(int i = 0; i < 8; i++) {
    if(chessBoard[king_y][i] == 2 || chessBoard[king_y][i] == 5) {
      int currentpiece = chessBoard[king_y][i];
      // check if the rook can capture
      if(currentpiece == 2){
        // check if the rook can capture
        if(blackCheckValid(2, i, king_y, king_x, king_y)){
          // a white tower is on the same line as the black king
          lcdString=("currently in check rook horizontal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if(currentpiece == 5){
        // check if the queen can capture
        if(blackCheckValid(5, i, king_y, king_x, king_y)){
          // a white queen is on the same line as the king
          lcdString=("currently in check queen horizontal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
  }

  // Check column
  for(int i = 0; i < 8; i++) {
    if(chessBoard[i][king_x] == 2 || chessBoard[i][king_x] == 5) {
      int currentpiece = chessBoard[i][king_x];
      // check if the rook can capture
      if(currentpiece == 2){
        // check if the rook can capture
        if(blackCheckValid(2, king_x, i, king_x, king_y)){
          // a white tower is on the same line as the black king
          lcdString=("currently in check rook vertical");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if(currentpiece == 5){
        // check if the queen can capture
        if(blackCheckValid(5, king_x, i, king_x, king_y)){
          // a white queen is on the same line as the black king
          lcdString=("currently in check queen vertical");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
  }

  // Check diagonal (top-left to bottom-right)
  int x = king_x;
  int y = king_y;
  while (x >= 0 && y >= 0) {
    if (chessBoard[y][x] == 4 || chessBoard[y][x] == 5) {
      int currentpiece = chessBoard[y][x];
      // check if the bishop can capture
        if (currentpiece == 4) {
          if (blackCheckValid(4, x, y, king_x, king_y)) {
            // a white bishop is on the same diagonal as the black king
            lcdString=("currently in check rook diagonal");
            // swap player back
            currentplayer = !currentplayer;
            return true;
          }
        }else if (currentpiece == 5) {
          if (blackCheckValid(5, x, y, king_x, king_y)) {
            // a white queen is on the same diagonal as the black king
            lcdString=("currently in check queen diagonal");
            // swap player back
            currentplayer = !currentplayer;
            return true;
          }
        }
      }
      x--;
      y--;
  }

  // Check diagonal (top-right to bottom-left)
  x = king_x;
  y = king_y;
  while (x < 8 && y >= 0) {
    if (chessBoard[y][x] == 4 || chessBoard[y][x] == 5) {
      int currentpiece = chessBoard[y][x];
      // check if the bishop can capture
      if (currentpiece == 4) {
        if (blackCheckValid(4, x, y, king_x, king_y)) {
          // a white bishop is on the same diagonal as the black king
          lcdString=("currently in check bishop diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if (currentpiece == 5) {
        if (blackCheckValid(5, x, y, king_x, king_y)) {
          // a white queen is on the same diagonal as the black king
          lcdString=("currently in check queen diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
    x++;
    y--;
  }

  // Check diagonal (bottom-left to top-right)
  x = king_x;
  y = king_y;
  while (x < 8 && y < 8) {
    if (chessBoard[y][x] == 4 || chessBoard[y][x] == 5) {
      int currentpiece = chessBoard[y][x];
      // check if the bishop can capture
      if (currentpiece == 4) {
        if (blackCheckValid(4, x, y, king_x, king_y)) {
          // a white bishop is on the same diagonal as the black king
          lcdString=("currently in check bishop diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if (currentpiece == 5) {
        if (blackCheckValid(5, x, y, king_x, king_y)) {
          // a white queen is on the same diagonal as the black king
          lcdString=("currently in check queen diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
    x++;
    y++;
  }

  // Check diagonal (bottom-right to top-left)
  x = king_x;
  y = king_y;
  while (x >= 0 && y < 8) {
    if (chessBoard[y][x] == 4 || chessBoard[y][x] == 5) {
      int currentpiece = chessBoard[y][x];
      // check if the bishop can capture
      if (currentpiece == 4) {
        if (blackCheckValid(4, x, y, king_x, king_y)) {
          // a white bishop is on the same diagonal as the black king
          lcdString=("currently in check bishop diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }else if (currentpiece == 5) {
        if (blackCheckValid(5, x, y, king_x, king_y)) {
          // a white queen is on the same diagonal as the black king
          lcdString=("currently in check queen diagonal");
          // swap player back
          currentplayer = !currentplayer;
          return true;
        }
      }
    }
    x--;
    y++;
  }

  // check if knight can attack
  int knight_moves_x[] = {2, 1, -1, -2, -2, -1, 1, 2};
  int knight_moves_y[] = {1, 2, 2, 1, -1, -2, -2, -1};

  for (int i = 0; i < 8; i++) {
    int knight_x = king_x + knight_moves_x[i];
    int knight_y = king_y + knight_moves_y[i];
    if (knight_x >= 0 && knight_x <= 7 && knight_y >= 0 && knight_y <= 7) {
      if (chessBoard[knight_y][knight_x] == 3) {
        // an opposing knight is attacking the black king
        lcdString=("currently in check by horsey");
        currentplayer = !currentplayer;
        return true;
      }
    }
  }

  // no cheque found
  currentplayer = !currentplayer;
  return false;
}

bool mateCheck(){
  lcdString=("not implemented yet");
}