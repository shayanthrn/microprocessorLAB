#include <SPI.h>

const int tempPin = A0;
const int ldrPin = A1;
const int Switch = A15;
const int Slave1_SS = 15;
const int Slave2_SS = 16;
//int vin;

char copy[50];
char copy_2[50];
char TransferedData;

void setup (void) {
   SPI.begin ();
   Serial.begin(9600);
   
   pinMode(Slave1_SS, OUTPUT);
   pinMode(Slave2_SS, OUTPUT);
   pinMode(Switch, INPUT);
    
   digitalWrite(Slave1_SS, HIGH);
   digitalWrite(Slave2_SS, HIGH);
   digitalWrite(SS, LOW);
}

void loop (void) {

/**** LM35 Sensor Calculate ****/
//  vin=analogRead(tempPin);
//  int Temperature = (500.0 * vin)/1023; 
  int Temperature = ( (analogRead(tempPin)/100)/1024.0)*5000;
  Temperature /= 10;
  sprintf(copy, "temp:%f\r", Temperature);

/**** LDR Sensor Calculate ****/
  int LDR_Value = analogRead(ldrPin)/100;
  sprintf(copy_2, "LDR:%f\r", LDR_Value);

/**** First Slave Data ****/   
   digitalWrite(Slave1_SS, LOW);
   for (const char * p = "Hello world\r" ; TransferedData = *p; p++) {
      SPI.transfer(TransferedData);
      Serial.println(TransferedData);
   }
   digitalWrite(Slave1_SS, HIGH);
   delay(20);
/**** Second Slave Data ****/
   digitalWrite(Slave2_SS, LOW);
   for (const char * p = "Hi\r" ; TransferedData = *p; p++) {
      SPI.transfer(TransferedData);
      Serial.println(TransferedData);
   }
   digitalWrite(Slave2_SS, HIGH);
   
  /* delay(200);
   digitalWrite(SS, HIGH);
   digitalWrite(SS, LOW);*/
   
/**** LM35 Data ****/   
   digitalWrite(Slave1_SS, LOW);
     for (const char * p = copy ; TransferedData = *p; p++) {
      SPI.transfer(TransferedData);
      Serial.println(TransferedData);
   }
   digitalWrite(Slave1_SS, HIGH);
   delay(30);
/**** LDR Sensor Data ****/
   digitalWrite(Slave2_SS, LOW);
     for (const char * p = copy_2 ; TransferedData = *p; p++) {
      SPI.transfer(TransferedData);
      Serial.println(TransferedData);
   }
   digitalWrite(Slave2_SS, HIGH);
   //delay(200);
}
