#include <Servo.h>

Servo myservo;
int read_value;
int converted_value;

void setup() {
  myservo.attach(6);
}

void loop() {
  read_value = analogRead(A0);
  converted_value = map(read_value, 0, 1023, 1000, 2000);
  myservo.writeMicroseconds(converted_value);
}
