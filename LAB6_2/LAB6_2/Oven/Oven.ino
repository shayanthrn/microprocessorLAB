#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>


LiquidCrystal lcd(13, 12, 5, 4, 3, 2);


const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
  {'7','8','9','/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'c', '0', '=', '+'}
};
byte rowPins[rows] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[cols] = {26, 27, 28, 29}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

//servo
Servo myservo;

const int buzPin = 0;
int analogPin = A0; // potentiometer wiper (middle terminal) connected to analog pin 3

//variables
int Vin;  // Variable to read the value from Arduino A0
float Temperature; // variable that receives the converted voltage
boolean heating;
boolean counting;
boolean door_is_close;
boolean finished;
float temp;
int timer;
int input;

//functions
int toInteger(char c) {
    return c - '0';
}

void reset(){
  heating = false;
  counting = false;
  door_is_close = false;
  finished = false;
  input = 0;
}
void turnOn(){
    myservo.write(150);
    tone(buzPin, 200);
    delay(300);
    noTone(buzPin);
}

void turnOff(){
    myservo.write(50);
    tone(buzPin, 200);
    delay(300);
    noTone(buzPin);
}
void recvTemp(){
  input = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  while(1){
    char key = keypad.getKey();
    if(key){
        if(key >= '0' && key <= '9'){
          input = input*10 + toInteger(key);
          lcd.print(key);
        }
        else if(key == '+') {
          temp = (float) input;
          lcd.clear();
          break;
        }
    }
  }
}

void recvTime(){
  input = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Timer:");
  lcd.setCursor(0, 1);
  while(1){
    char key = keypad.getKey();
    if(key){
        if(key >= '0' && key <= '9'){
          input = input*10 + toInteger(key);
          lcd.print(key);
        }
        else if(key == '+') {
          timer = input;
          lcd.clear();
          break;
        }
    }
  }
}


void heater(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("heating... ");
  float heat = Temperature;
  float check = temp - heat;
  while(abs(check) > 0.6){
     delay(300);
     heat += 1.2;
     lcd.setCursor(0, 1);
     lcd.print(heat);
     check = temp - heat;
  }
  counting = true;
}

void cook(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("timer ");
  int counter = timer;
  for(int i = 0; i < timer; i++){
     lcd.setCursor(0, 1);
     lcd.print(counter);
     counter--;
     delay(500);
  }
  if(counter == 0){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Finished");
  }
  turnOff();
  reset();
}

void setup() {
    //LCD
   lcd.begin(16,2);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Hassan Kazemi");
   lcd.setCursor(0, 1);
   lcd.print("Oven");
   delay(500);
   lcd.clear();
   

   //servo
   myservo.attach(6);
   myservo.write(50);

  //buzeer
   pinMode(buzPin,OUTPUT);
  //temperature sensor
  pinMode(analogPin,INPUT);
  Serial.begin(9600);
   //initilization
   Vin = analogRead(analogPin);    //Tell the Arduino to read the voltage on pin A0
   Temperature = (500.0 * Vin)/1023; // Convert the read value into a voltage
   heating = false;
   counting = false;
   door_is_close = false;
   finished = false;
   input = 0;

   delay(500);
   lcd.setCursor(0, 0);
   lcd.print("current temp:");
   lcd.setCursor(0, 1);
   lcd.print(Temperature);
   delay(1000);
   lcd.clear();
}

void loop() {
   //scan the entered password
  char key = keypad.getKey();
  if(key){
    if(key == '/') recvTemp();
    else if(key == '*') recvTime();
    else if(key == '=') finished = true; 
  }
  //turn on the oven
  if(finished && !door_is_close){
    turnOn();
    door_is_close = true;
    heating = true;  
  }
  if(heating && !counting){
    heater();  
  }
  if(counting){ 
    cook(); 
  }

}
