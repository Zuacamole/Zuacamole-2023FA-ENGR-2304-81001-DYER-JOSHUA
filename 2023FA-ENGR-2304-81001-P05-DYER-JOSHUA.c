/*

2023FA-ENGR-2304-81001-DYER-JOSHUA-P05

https://www.tinkercad.com/things/ev2LU1qOMld

*/

#include <LiquidCrystal.h>

// Initialize the library by associating any needed LCD interface pins
// with the Arduino pin numbers they are connected to
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // Set the cursor to column 0, line 1 
  // (note: line 1 is the second row, as counting begins with 0):
  lcd.setCursor(0, 1);
  
  // Print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
