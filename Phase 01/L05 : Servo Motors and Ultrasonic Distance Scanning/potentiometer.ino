
#include <Servo.h>
Servo myServo;
int potValue = 0;
int angle = 0;
void setup() {
  myServo.attach(9);
  Serial.begin(9600);
}
void loop() {
  potValue = analogRead(A0);
  angle = map(potValue, 0, 1023, 0, 180);
  myServo.write(angle);
  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print(" | Angle: ");
  Serial.println(angle);
  delay(15);
}

