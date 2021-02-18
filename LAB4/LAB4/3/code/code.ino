#include <Servo.h>

Servo myservo;
int read_value;
int converted_value;

void setup() {
  myservo.attach(6);
  Serial.begin(9600);
}

void loop() {
}

void serialEvent() {
  read_value = Serial.parseInt();
  converted_value = map(read_value,-90, 90, 1000, 2000);
  Serial.print("read value is: ");
  Serial.println(read_value);
  Serial.print("Converted value is: ");
  Serial.println(converted_value);
  myservo.writeMicroseconds(converted_value);
}
