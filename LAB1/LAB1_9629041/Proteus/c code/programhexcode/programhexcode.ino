// initialize push buttons
int upper_button;
int middle_button;
int bottom_button;
// initialize leds:
int led_1;
int led_2;
int led_3;
int led_4;
int led_5;
int led_6;
int led_7;

void setup() {
  // inputs:
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  // outputs:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

}

void loop() {  
  // read button values:
  upper_button = digitalRead(10);
  middle_button = digitalRead(11);
  bottom_button = digitalRead(12);
  // read LED values (from left to right):
  led_1 = digitalRead(6);
  led_2 = digitalRead(5);
  led_3 = digitalRead(4);
  led_4 = digitalRead(3);
  led_5 = digitalRead(2);
  led_6 = digitalRead(1);
  led_7 = digitalRead(0);

  // when user pushes upper button:
  if (upper_button == LOW) {
      digitalWrite(6, HIGH);
      delay(500);
      digitalWrite(5, HIGH);
      delay(500);
      digitalWrite(4, HIGH);
      delay(500);
      digitalWrite(3, HIGH);
      delay(500);
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(1, HIGH);
      delay(500);
      digitalWrite(0, HIGH);
      delay(500);
  }
  
  // when user pushes middle button:
  if (middle_button == LOW) {
      digitalWrite(0, HIGH);
      delay(500);
      digitalWrite(1, HIGH);
      delay(500);
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(3, HIGH);
      delay(500);
      digitalWrite(4, HIGH);
      delay(500);
      digitalWrite(5, HIGH);
      delay(500);
      digitalWrite(6, HIGH);
      delay(500);
  }

  // when user pushes bottom button:
  if (bottom_button == LOW) {
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
}
