#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(6);
}

void loop() {
  delay(1000);
  myservo.write(180);
  delay(1000);
  myservo.write(0);
}
