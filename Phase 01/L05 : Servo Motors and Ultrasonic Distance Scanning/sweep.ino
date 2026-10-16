
#include <Servo.h>
Servo myServo;
void setup() {
  myServo.attach(9);
}
void loop() {
  // Move from 0 degrees to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(15);
  }
  // Move from 180 degrees back to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}
