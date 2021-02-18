#include <SPI.h>
bool process;
char buff [50];
volatile byte indx;

void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT); 
  SPCR |= _BV(SPE);
  process = false;
  SPI.attachInterrupt();

}

ISR (SPI_STC_vect)
{
  byte c = SPDR;
  if ( (indx < sizeof buff) ) {
  buff [indx++] = c; 
  if (c == '\r') 
  process = true;
  } 
}

void loop() {
  if (process) {
    process = false;
    Serial.println(buff);
    delay(200);
  }
}





















