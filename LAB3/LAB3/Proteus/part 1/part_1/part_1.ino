#include <LiquidCrystal.h>
#include <Keypad.h>
 
const byte ROWS = 4;
const byte COLS = 4;
 
char keys[ROWS][COLS] = {
 
  {'7','8','9','/'},
 
  {'4','5','6','*'},
 
  {'1','2','3','-'},
 
  {'C','0','=','+'}
 
};
 
byte rowPins[ROWS] = { 0, 1, 2, 3 };
byte colPins[COLS] = { 4, 5, 6, 7 };
 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int max_length;
int current_line;

int change_line(){
  if (current_line == 0)
    return 1;
  else
    return 0;
}


void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hassan Kazemi");
  max_length = 16;
  current_line = 0;
}
 
void loop() {
  for (int positionCounter = 0; positionCounter < max_length; positionCounter++) {
    lcd.scrollDisplayLeft();
  }
  delay(150);
  for (int positionCounter = 0; positionCounter < 16 + max_length; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  lcd.clear();
  current_line = change_line();
  lcd.setCursor(0, current_line);
  lcd.print("Hassan Kazemi");
}
