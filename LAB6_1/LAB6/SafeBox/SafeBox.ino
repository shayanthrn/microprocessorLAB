#include <Servo.h>
#include <LiquidCrystal.h> 
#include <Keypad.h>

Servo myservo;

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
 
// Define the Keymap
char keys[ROWS][COLS] = {
 
  {'1','2','3'},
 
  {'4','5','6'},
 
  {'7','8','9'},
 
  {'*','0','#'}
 
};
 
byte rowPins[ROWS] = { 14, 15, 16, 17 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 18, 19, 20 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad
 
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13; //Pins to which LCD is connected
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
long user_input;
long open_timeout = 5000;
long accepted_password = 123;
long start_time;
char key;
boolean result = false;
boolean is_safebox_open = false;
boolean change_pass_entered_correctly = false;
enum modes{Normal,ChangePass,ChangeTimeout};
modes mode = Normal;

const int LED_red = 22;
const int LED_green= 23;
const int buzzer = 24;
const int close_button = 26;
const int change_pass_button = 27;
const int change_timeout_button = 28;

void setup() {
  lcd.begin(16, 2); //We are using a 16*2 LCD display
  lcd.print("SafeBox"); //Display a intro message
  lcd.setCursor(0, 1);   // set the cursor to column 0, line 1
  lcd.print("Hassan Kazemi"); //Display a intro message 
 
  delay(2000); //Wait for display to show info
  lcd.clear(); //Then clean it

  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(close_button, INPUT);

  myservo.attach(6);
}
 
void loop() {
  key = kpd.getKey(); //storing pressed key value in a char
   
  if (key!=NO_KEY)
    detect_buttons();
  

  if (digitalRead(close_button) == HIGH) {
    close_safebox();
    result = false;
  }
  if (digitalRead(change_pass_button) == HIGH) { 
    lcd.clear();
    user_input = 0;
    mode = ChangePass;
  }
  if (digitalRead(change_timeout_button) == HIGH){
    lcd.clear();
    user_input = 0;
    mode = ChangeTimeout;
  }
  
  if (is_safebox_open && (millis() >= start_time + open_timeout))
    close_safebox();
  
  display_result();
}
 
void detect_buttons() { 
    lcd.clear(); //Then clean it
    if (key=='#') { //If cancel Button is pressed
      user_input=0;
      result = false;
    }

    if (key >= '0' && key <= '9') {
        if (user_input * 10 < 999999999) {
          user_input = (user_input*10) + (key - 48);
          result = false;
        }
    }

    if (key == '*')
      result = true; 
}

void buzz_now(int frequency) {
  tone(buzzer, frequency); 
  delay(200);        
  noTone(buzzer);   
}

void open_safebox() {
  buzz_now(200);
  myservo.writeMicroseconds(1000);
  is_safebox_open = true;
  start_time = millis();
}

void close_safebox() {
  if (is_safebox_open){
    buzz_now(50);
    myservo.writeMicroseconds(1500);
    is_safebox_open = false;
    result = false;
    lcd.clear();
  }
}

void display_result() {
  if (mode == Normal)
    show_normal();
  if (mode == ChangePass)
    show_change_pass();
  if (mode == ChangeTimeout)
    show_change_timeout();
}

void change_mode_to_normal() {
    mode = Normal;
    user_input = 0;
    result = false;
    lcd.clear();
}

void show_change_timeout() {
  lcd.setCursor(0, 0);
  if (!change_pass_entered_correctly) {
      lcd.print("Current pass: ");
      lcd.setCursor(0, 1);
      if (result == false)
        lcd.print(user_input);
      else {
        if (user_input == accepted_password) {
          change_pass_entered_correctly = true;
          lcd.clear();
          user_input = 0;
          result = false;
        }
        else {
          lcd.print("Wrong password");
        }
      }
    }
    
    else {
      lcd.print("timeout(sec): ");
      lcd.setCursor(0, 1);
      lcd.print(user_input);
      if (result == true) {
        open_timeout = user_input * 1000;
        lcd.setCursor(0, 1);
        lcd.print("timeout Changed");
        delay(1000);
        change_mode_to_normal();
      }
    }
}

void show_change_pass() {
    lcd.setCursor(0, 0);
    if (!change_pass_entered_correctly) {
      lcd.print("Current pass: ");
      lcd.setCursor(0, 1);
      if (result == false)
        lcd.print(user_input);
      else {
        if (user_input == accepted_password) {
          change_pass_entered_correctly = true;
          lcd.clear();
          user_input = 0;
          result = false;
        }
        else {
          lcd.print("Wrong password");
        }
      }
    }
    
    else {
      lcd.print("New pass: ");
      lcd.setCursor(0, 1);
      lcd.print(user_input);
      if (result == true) {
        accepted_password = user_input;
        lcd.setCursor(0, 1);
        lcd.print("Pass Changed");
        delay(1000);
        change_mode_to_normal();
        change_pass_entered_correctly = false;
      }
    }
}

void show_normal() {
  lcd.setCursor(0, 0);
  if (result == false)
    lcd.print(user_input);
  
  if (result==true) {
    if (user_input == accepted_password){
      lcd.print("Correct!");
      if (!is_safebox_open)
        open_safebox();
    }
    else {
      lcd.print("Wrong Password");
    }
  }
  
  if (is_safebox_open) {
    digitalWrite(LED_green, HIGH);
    digitalWrite(LED_red, LOW);
 
    lcd.setCursor(0, 1);
    lcd.print("close in ");
    lcd.print(((start_time + open_timeout + 1000) - millis()) / 1000);
    lcd.print(" sec");
  }
  else {
    digitalWrite(LED_green, LOW);
    digitalWrite(LED_red, HIGH);
    
    lcd.setCursor(0, 1);
    lcd.print("It's closed");
  }
}
