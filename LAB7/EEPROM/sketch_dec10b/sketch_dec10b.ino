#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Wire.h>

//defines the writeEEPROM function
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data );
//defines the readEEPROM function
byte readEEPROM(int deviceaddress, unsigned int eeaddress );
//Mode show function
void Mode_Show();
//keypad Mode selection
void keypad_Mode_Set();
// time counter
int timecounter();
// Set Proccess Time
void Set_Proccess_Time();

#define eeprom 0x50 //defines the base address of the EEPROM
unsigned int address = 0; //first address of the EEPROM
boolean STR_Flag = false;  //start flag
unsigned int STP = 0; //timer_stop flag
unsigned int sec_ = 0 , min_ = 0 , hour_ = 0;
char key;

unsigned int LED1 = 14;
unsigned int LED2 = 15;
unsigned int LED3 = 16;
unsigned int LED4 = 17;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 6, 7, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int RS = 13, E = 12, D4 = 11, D5 = 10, D6 = 9, D7 = 8;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup() {
  
  Wire.begin(); 
  lcd.begin(16, 2);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  lcd.setCursor(1,0);
  lcd.print("Hi Dear User:)");
  delay(2000);
  lcd.clear();
  Mode_Show();
}

void loop() {

 lcd.setCursor(1,0); lcd.print("ON/C for Start"); lcd.setCursor(2,1); lcd.print(" = for Stop");
 
 if(keypad.getKey()=='*'){
    STR_Flag = true;
 }

 if(STR_Flag){
  
  lcd.clear();
    keypad_Mode_Set();
      Set_Proccess_Time();
        lcd.clear();
      while(1){ 
        STP = timecounter();
        lcd.setCursor(1,0); lcd.print("REMAINING TIME");
        lcd.setCursor(5,1); lcd.print(hour_); lcd.print(":"); lcd.print(min_); lcd.print(":"); lcd.print(sec_);
        key=keypad.getKey();
        if(key){
         if(key=='A'){
          lcd.setCursor(0,1); lcd.print("                "); 
          lcd.setCursor(5,1); lcd.print("PAUSE"); 
          while(1){
            key=keypad.getKey();
               if(key=='D'){
                    lcd.setCursor(0,1); lcd.print("                ");
                    break;
                 }
               }
             } else if(key=='#'){
                    STP=1;
                    break;
              } 
           } 
        if(STP == 1){
           lcd.clear();
           lcd.setCursor(0,0); lcd.print("Finish!Press Any"); lcd.setCursor(3,1); lcd.print("Key to exit");
           digitalWrite(LED1, HIGH);
           digitalWrite(LED2, HIGH);
           digitalWrite(LED3, HIGH);
           digitalWrite(LED4, HIGH);
           while(!keypad.getKey()){} 
           lcd.clear();  
           STR_Flag = false;
           STP=0;
           break;
        }   
        delay(850);
     }    
   }
 }

// Set Proccess Time
void Set_Proccess_Time(){
  
  int charCounter=0;
   int num1=0 , num2=0 , num3=0;
     lcd.setCursor(1,0); lcd.print("Enter Time And"); lcd.setCursor(3,1); lcd.print("Press ON/C");
     while(!keypad.getKey()){}
     lcd.clear(); 
     lcd.setCursor(2,0); lcd.print("Enter Second"); lcd.setCursor(5,1); lcd.print("sec:");       
     
   while(1){
    key = keypad.getKey(); 
     if(key=='*' || charCounter>2){
       sec_ = num1; 
       charCounter=0;
       break;
     }
      if(key){
       if(key >='0' && key <='9' && charCounter<2){ 
         lcd.print(key);
         num1 = num1*10 + (key -'0');
         charCounter++;
       }
     }
   }

     lcd.clear(); 
     lcd.setCursor(2,0); lcd.print("Enter Minute"); lcd.setCursor(5,1); lcd.print("min:");       
     
   while(1){
    key = keypad.getKey();
     if(key=='*' || charCounter>2){
       min_ = num2;
       charCounter=0; 
       break;
     } 
      if(key){
       if(key >='0' && key <='9' && charCounter<2){ 
         lcd.print(key);
         num2 = num2*10 + (key -'0');
         charCounter++;
       }
     }
   }

     lcd.clear(); 
     lcd.setCursor(3,0); lcd.print("Enter hour"); lcd.setCursor(5,1); lcd.print("hour:");       
     
   while(1){
    key = keypad.getKey();
     if(key=='*' || charCounter>2){
       hour_ = num3; 
       charCounter=0;
       break;
     } 
      if(key){
       if(key >='0' && key <='9' && charCounter<2){ 
         lcd.print(key);
         num3 = num3*10 + (key -'0');
         charCounter++;
       }
      }
   }
}

// time counter
int timecounter(){

    if(sec_ !=0) sec_-=1;

    if(hour_ == 0 && min_ == 0 && sec_ == 0) return 1; 

    if(sec_ <10) lcd.setCursor(4,1); lcd.print("                ");    

    if(sec_ == 0)
    {
      lcd.setCursor(1,1); lcd.print("                ");
      sec_= 60;
      if(min_ !=0) min_-=1;
    }
    
    if(min_ == 0 && sec_ == 0)
    {
      lcd.setCursor(1,1); lcd.print("                ");
      min_= 60;
      if(hour_ !=0) hour_-=1;
    }
    
    return 0;
}

//keypad Mode selection
void keypad_Mode_Set(){
  
 lcd.clear(); 
 lcd.setCursor(1,0); lcd.print("Select device"); lcd.setCursor(0,1); lcd.print("mode with keypad"); 
  while(1){
   char key = keypad.getKey();
    if (key){
      if(key=='1'){
        address = 1;
        writeEEPROM(eeprom, address, 0);
        delay(10);
        Mode_Show();
        break;
      }
      else if(key=='2'){
        address = 1;
        writeEEPROM(eeprom, address, 1);
        delay(10);
        Mode_Show();
        break;
      }
      else if(key=='3'){
        address = 1;
        writeEEPROM(eeprom, address, 2);
        delay(10);
        Mode_Show();
        break;
      }
      else if(key=='4'){
        address = 1;
        writeEEPROM(eeprom, address, 3);
        delay(10);
    Mode_Show();
    break;
      }
    }
  }
}

//Mode show function
void Mode_Show(){

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  lcd.clear();
  address = 1;
  unsigned int Mode = readEEPROM(eeprom, address);
  delay(10);
  
  if(Mode == 0){
    lcd.setCursor(4,0); lcd.print("Pre wash"); lcd.setCursor(6,1); lcd.print("Mode");
    digitalWrite(LED1, HIGH); 
  }
  else if(Mode == 1){
    lcd.setCursor(3,0); lcd.print("Wash with"); lcd.setCursor(1,1); lcd.print("Detergent Mode");
    digitalWrite(LED2, HIGH); 
  }
  else if(Mode == 2){
    lcd.setCursor(0,0); lcd.print("Wash with water"); lcd.setCursor(5,1); lcd.print("Mode");
    digitalWrite(LED3, HIGH); 
  }
  else if(Mode == 3){
    lcd.setCursor(1,0); lcd.print("Clothes dryer"); lcd.setCursor(5,1); lcd.print("Mode");
    digitalWrite(LED4, HIGH); 
  }
  else{
    keypad_Mode_Set();
    return;
  }
  delay(2000);
  lcd.clear();
}

//defines the writeEEPROM function
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));      //writes the MSB
  Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
  Wire.write(data);
  Wire.endTransmission();
  }

  //defines the readEEPROM function
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));      //writes the MSB
  Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
  Wire.endTransmission(false);
  Wire.requestFrom(deviceaddress,1);
  if (Wire.available()) 
    rdata = Wire.read();
  return rdata;
  }
