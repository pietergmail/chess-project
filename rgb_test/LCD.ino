String firstString;
String secondString;

// Used for string compare
String White = "White";
String Black = "Black";


void LCD_display(){
  Serial.println(lcdstring);
  // split the string into 2
  firstString = lcdstring.substring(0, 16);
  secondString = lcdstring.substring(16);

  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print(firstString);        // print message at (0, 0)
  lcd.setCursor(0, 1);         // move cursor to   (0, 1)
  lcd.print(secondString);        // print message at (0, 1)
}