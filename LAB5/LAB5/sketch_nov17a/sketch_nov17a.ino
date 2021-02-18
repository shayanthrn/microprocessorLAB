void setup() {
  pinMode(52,OUTPUT);
//  pinMode(53,OUTPUT);
}

void loop() {
 
    digitalWrite(52,LOW);
      
    delay(1000); 
    digitalWrite(52,HIGH);
    delay(1000); 
}
