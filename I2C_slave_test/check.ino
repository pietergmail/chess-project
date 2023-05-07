// not full logic, save on compute
bool checkCheck(){
  // give initial values to avoid errors
  int king_y = 10;
  int king_x = 10;

  if(currentplayer){
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
    // check if there is a rook or queen horizontally/vertically
    // Check row
    for(int i = 0; i < 8; i++) {
        if(chessBoard[king_y][i] == 8 || chessBoard[king_y][i] == 11) {
            int currentpiece = chessBoard[king_y][i];
            // swap current player for check temporarely
            currentplayer = !currentplayer;
            // check if the rook can capture
            if(currentpiece == 8){
              // check if the rook can capture
              if(whiteCheckValid(8, i, king_y, king_x, king_y)){
                // a white tower is on the same line as the black king
                Serial.println("currently in check");
                currentplayer = !currentplayer;
                return true;
              }
            }else if(currentpiece == 11){
              // check if the queen can capture
              if(whiteCheckValid(11, i, king_y, king_x, king_y)){
                // a white queen is on the same line as the king
                Serial.println("currently in check");
                currentplayer = !currentplayer;
                return true;
              }
            }
        }
    }
    // Check column
    for(int i = 0; i < 8; i++) {
        if(chessBoard[i][king_x] == 8 || chessBoard[i][king_x] == 11) {
          int currentpiece = chessBoard[king_y][i];
          // swap current player for check temporarely
          currentplayer = !currentplayer;
          // check if the rook can capture
          if(currentpiece == 9){
            // check if the rook can capture
            if(whiteCheckValid(9, king_x, i, king_x, king_y)){
              // a white tower is on the same line as the black king
              Serial.println("currently in check");
              currentplayer = !currentplayer;
              return true;
            }
          }else if(currentpiece == 11){
            // check if the queen can capture
            if(whiteCheckValid(11, king_x, i, king_x, king_y)){
              // a white queen is on the same line as the black king
              Serial.println("currently in check");
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
        if (chessBoard[y][x] == 9 || chessBoard[y][x] == 11) {
            int currentpiece = chessBoard[y][x];
            // swap current player for check temporarily
            currentplayer = !currentplayer;
            // check if the bishop can capture
            if (currentpiece == 9) {
                if (whiteCheckValid(9, x, y, king_x, king_y)) {
                    // a white bishop is on the same diagonal as the black king
                    Serial.println("currently in check");
                    currentplayer = !currentplayer;
                    return true;
                }
            }
            // check if the queen can capture
            else if (currentpiece == 11) {
                if (whiteCheckValid(11, x, y, king_x, king_y)) {
                    // a white queen is on the same diagonal as the black king
                    Serial.println("currently in check");
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
        if (chessBoard[y][x] == 9 || chessBoard[y][x] == 11) {
            int currentpiece = chessBoard[y][x];
            // swap current player for check temporarily
            currentplayer = !currentplayer;
            // check if the bishop can capture
            if (currentpiece == 9) {
                if (whiteCheckValid(9, x, y, king_x, king_y)) {
                    // a white bishop is on the same diagonal as the black king
                    Serial.println("currently in check");
                    currentplayer = !currentplayer;
                    return true;
                }
            }
            // check if the queen can capture
            else if (currentpiece == 11) {
                if (whiteCheckValid(11, x, y, king_x, king_y)) {
                    // a white queen is on the same diagonal as the black king
                    Serial.println("currently in check");
                    currentplayer = !currentplayer;
                    return true;
                }
            }
        }
        x++;
        y--;
    }
    // Check front-left and front-right for opposing pawn
    if (king_x - 1 >= 0 && king_y + 1 >= 0 && king_x - 1 <= 7 && king_y + 1 <= 7) {
        if (chessBoard[king_y + 1][king_x - 1] == 1) {
            // a white pawn is to the front-left of the black king
            Serial.println("currently in check");
            return true;
        }
    }
    if (king_x + 1 >= 0 && king_y + 1 >= 0 && king_x + 1 <= 7 && king_y + 1 <= 7) {
        if (chessBoard[king_y + 1][king_x + 1] == 1) {
            // a white pawn is to the front-right of the black king
            Serial.println("currently in check");
            return true;
        }
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
              Serial.println("currently in check");
              return true;
          }
      }
    }
  }else{
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
    // check if there is a rook or queen horizontally/vertically
    // Check row
    for(int i = 0; i < 8; i++) {
        if(chessBoard[king_y][i] == 8 || chessBoard[king_y][i] == 11) {
            int currentpiece = chessBoard[king_y][i];
            // swap current player for check temporarely
            currentplayer = !currentplayer;
            // check if the rook can capture
            if(currentpiece == 8){
              // check if the rook can capture
              if(whiteCheckValid(8, i, king_y, king_x, king_y)){
                // a white tower is on the same line as the black king
                Serial.println("currently in check");
                currentplayer = !currentplayer;
                return true;
              }
            }else if(currentpiece == 11){
              // check if the queen can capture
              if(whiteCheckValid(11, i, king_y, king_x, king_y)){
                // a white queen is on the same line as the king
                Serial.println("currently in check");
                currentplayer = !currentplayer;
                return true;
              }
            }
        }
    }
    // Check column
    for(int i = 0; i < 8; i++) {
        if(chessBoard[i][king_x] == 8 || chessBoard[i][king_x] == 11) {
          int currentpiece = chessBoard[king_y][i];
          // swap current player for check temporarely
          currentplayer = !currentplayer;
          // check if the rook can capture
          if(currentpiece == 9){
            // check if the rook can capture
            if(whiteCheckValid(9, king_x, i, king_x, king_y)){
              // a white tower is on the same line as the black king
              Serial.println("currently in check");
              currentplayer = !currentplayer;
              return true;
            }
          }else if(currentpiece == 11){
            // check if the queen can capture
            if(whiteCheckValid(11, king_x, i, king_x, king_y)){
              // a white queen is on the same line as the black king
              Serial.println("currently in check");
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
        if (chessBoard[y][x] == 9 || chessBoard[y][x] == 11) {
            int currentpiece = chessBoard[y][x];
            // swap current player for check temporarily
            currentplayer = !currentplayer;
            // check if the bishop can capture
            if (currentpiece == 9) {
                if (whiteCheckValid(9, x, y, king_x, king_y)) {
                    // a white bishop is on the same diagonal as the black king
                    Serial.println("currently in check");
                    currentplayer = !currentplayer;
                    return true;
                }
            }
            // check if the queen can capture
            else if (currentpiece == 11) {
                if (whiteCheckValid(11, x, y, king_x, king_y)) {
                    // a white queen is on the same diagonal as the black king
                    Serial.println("currently in check");
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
        if (chessBoard[y][x] == 9 || chessBoard[y][x] == 11) {
            int currentpiece = chessBoard[y][x];
            // swap current player for check temporarily
            currentplayer = !currentplayer;
            // check if the bishop can capture
            if (currentpiece == 9) {
                if (whiteCheckValid(9, x, y, king_x, king_y)) {
                    // a white bishop is on the same diagonal as the black king
                    Serial.println("currently in check");
                    currentplayer = !currentplayer;
                    return true;
                }
            }
            // check if the queen can capture
            else if (currentpiece == 11) {
                if (whiteCheckValid(11, x, y, king_x, king_y)) {
                    // a white queen is on the same diagonal as the black king
                    Serial.println("currently in check");
                    currentplayer = !currentplayer;
                    return true;
                }
            }
        }
        x++;
        y--;
    }
    // Check front-left and front-right for opposing pawn
    if (king_x - 1 >= 0 && king_y + 1 >= 0 && king_x - 1 <= 7 && king_y + 1 <= 7) {
        if (chessBoard[king_y + 1][king_x - 1] == 1) {
            // a white pawn is to the front-left of the black king
            Serial.println("currently in check");
            return true;
        }
    }
    if (king_x + 1 >= 0 && king_y + 1 >= 0 && king_x + 1 <= 7 && king_y + 1 <= 7) {
        if (chessBoard[king_y + 1][king_x + 1] == 1) {
            // a white pawn is to the front-right of the black king
            Serial.println("currently in check");
            return true;
        }
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
              Serial.println("currently in check");
              return true;
          }
      }
    }
  }
  return false;
}

bool mateCheck(){
  Serial.println("not implemented yet");
}