#include <Servo.h>
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

byte rowPins[ROWS] = { 22, 23, 24, 25 };
byte colPins[COLS] = { 26, 27, 28, 29 };
 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
long Number;
char key,action;
boolean result = false;

Servo myservo;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Servo Motor");
  lcd.setCursor(0, 1);
  lcd.print("Hassan Kazemi");
  delay(2000);
  lcd.clear();
  myservo.attach(6);
}
 
void loop() {
  key = kpd.getKey();
  if (key)
    DetectButtons();
  ChangeTheAngles();   
}
 
void DetectButtons() { 
    lcd.clear();
    if (key=='C') {
      Number=0;
      result=false;
    }
    if (key >= '0' && key <= '9')
      if (((Number*10) + (key - 48)) <= 180) {
        Number = (Number*10) + (key - 48);
        result=false;
      }

    if (key == '*')
      result = true;  
}
 
void ChangeTheAngles() {
  lcd.setCursor(0, 0);
  lcd.print(Number);
  if (result==true)
    myservo.writeMicroseconds(map(Number, 0, 180, 1000, 2000));
}
