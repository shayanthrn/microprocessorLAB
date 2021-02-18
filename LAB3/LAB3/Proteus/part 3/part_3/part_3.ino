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
 
long Num1,Num2,Number;
char key,action;
boolean result = false;
 
void setup() {
  lcd.begin(16, 2);
  lcd.print("Calculator");
  lcd.setCursor(0, 1);
  lcd.print("Hassan Kazemi");
  delay(1000);
  lcd.clear();
}
 
void loop() {
  key = kpd.getKey();
  if (key)
    DetectButtons();
  if (result==true)
    CalculateResult();
  DisplayResult();   
}
 
void DetectButtons() { 
    lcd.clear();
    if (key=='C') {
      Number=Num1=Num2=0;
      action=' ';
      result=false;
    }
    if (key >= '0' && key <= '9')
      Number = (Number*10) + (key - 48);
    if (key == '=') {
      Num2 = Number;
      result = true;  
    }    
    if (key == '+' || key == '-' || key == '/' || key == '*')
    {
      Num1 = Number;    
      Number =0;
      if (key == '+')
        action = '+';
      if (key == '-')
        action = '-'; 
      if (key == '*')
        action = '*';
      if (key == '/')
        action = '/';
      delay(100);
    }
}
 
void CalculateResult() {
  if (action=='+')
    Number = Num1+Num2;
  if (action=='-')
    Number = Num1-Num2;
  if (action=='*')
    Number = Num1*Num2;
  if (action=='/')
    Number = Num1/Num2; 
}
 
void DisplayResult() {
  lcd.setCursor(0, 0);
  lcd.print(Num1);
  lcd.print(action);
  lcd.print(Num2); 
  if (result==true) {
    lcd.print(" =");
    lcd.print(Number);
  }  
  lcd.setCursor(0, 1);
  lcd.print(Number);
}
