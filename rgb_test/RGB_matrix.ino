// changes array to led representation of a chess board
// leds oriented witch connections on top right
void ArrayToLeds(int p[8][8]) {
  for (int i = 0; i < 8; i++) {
  // Iterate through the columns
    for (int j = 0; j < 8; j++) {
      // Print the element at the current row and column
      Serial.print(p[i][j]);
      Serial.print("\t"); // Add a tab between elements for better readability
    }
  Serial.println(); // Move to the next line after each row
  }
  
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      int value = p[x][y];

      // change coordinates to correct number
      int cor = y * 8 + x;

      // check which pieces is at set location
      switch (value) {
        case 0: { leds[0][cor] = CRGB(0, 0, 0); break;} // empty
        case 1: { leds[0][cor] = CRGB(255, 0, 0); break;} // Black pawn
        case 2: { leds[0][cor] = CRGB::Blue; break;} // Black rook
        case 3: { leds[0][cor] = CRGB(128, 255, 0); break;} // Black knight
        case 4: { leds[0][cor] = CRGB(0, 255, 0); break;} // Black bishop
        case 5: { leds[0][cor] = CRGB(111, 0, 255); break;} // Black queen
        case 6: { leds[0][cor] = CRGB(20, 20, 20); break;} // Black king
        // white pieces use lighter variants of the black pieces
        case 7: { leds[0][cor] = CRGB(255, 80, 0); break;} // white pawn
        case 8: { leds[0][cor] = CRGB(0, 239, 255); break;} // white rook
        case 9: { leds[0][cor] = CRGB::Yellow; break;} // white knight
        case 10: { leds[0][cor] = CRGB(0, 175, 23); break;} // white bishop
        case 11: { leds[0][cor] = CRGB(255, 0, 179); break;} // white queen
        case 12: { leds[0][cor] = CRGB::White; break;} // white king
      }
    }
  }
  FastLED. show();
}

// blink the currently selected piece, may need to be implemented differently
void blink(int x, int y){
  // change coordinates to correct number, needs to be redone
  int cor = y * 8 + x;
  CRGB old_color= CRGB(leds[0][cor].r, leds[0][cor].g, leds[0][cor].b);
  leds[0][cor] = CRGB::Black;
  FastLED.show();
  delay(500);
  leds[0][cor] = old_color;
  FastLED.show();
  delay(500);
}
