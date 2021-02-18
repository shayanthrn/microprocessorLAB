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

long Number;
long valid_password = 123456;
char key;
boolean result = false;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Password Checker");
  lcd.setCursor(0, 1);
  lcd.print("Hassan Kazemi");
  delay(1000);
  lcd.clear();
}
 
void loop() {
  key = kpd.getKey();
  if (key)
    DetectButtons();
  DisplayResult();  
}
void DetectButtons() { 
    lcd.clear();
    if (key=='C') {
      Number=0;
      result=false;
    }
    if (key >= '0' && key <= '9') {
      Number = (Number*10) + (key - 48);
      result = false;
    }
    if (key == '*')
      result = true;  
}
 
void DisplayResult() {
  lcd.setCursor(0, 0);
  if (result==true) {
    if ( Number == valid_password )
      lcd.print("Correct Password");
    else
      lcd.print("Wrong Password");
  }
  lcd.setCursor(0, 1);
  lcd.print(Number);
}
