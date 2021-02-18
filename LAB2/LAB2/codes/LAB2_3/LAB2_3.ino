#include <Keypad.h>

int inputfromVT;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'o','0','=','+'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {29, 27, 25,23}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(A6,OUTPUT);
  pinMode(A7,OUTPUT);
  pinMode(A8,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputfromVT=Serial.parseInt();
  if(inputfromVT!=0){
    Serial.print("\nI recieved : ");
    Serial.println(inputfromVT);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(A6, LOW);
  digitalWrite(A7, LOW);
  digitalWrite(A8, LOW);
    if(inputfromVT==1){
      digitalWrite(A0, HIGH );
  }
    if(inputfromVT==2){
      digitalWrite(A1, HIGH );
  }
    if(inputfromVT==3){
      digitalWrite(A2, HIGH );
  }
    if(inputfromVT==4){
      digitalWrite(A3, HIGH );
  }
    if(inputfromVT==5){
      digitalWrite(A4, HIGH );
  }
    if(inputfromVT==6){
      digitalWrite(A5, HIGH );
  }
    if(inputfromVT==7){
      digitalWrite(A6, HIGH );
  }
    if(inputfromVT==8){
      digitalWrite(A7, HIGH );
  }
    if(inputfromVT==9){
      digitalWrite(A8, HIGH );
  }
  }
}
