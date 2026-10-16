#include <Servo.h>
Servo scanner;
const int TRIG_PIN = 7;
const int ECHO_PIN = 6;
const int SERVO_PIN = 9;
const int STOP_DISTANCE = 20;
long duration;
int distance;
int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  if (duration == 0) {
    return -1;
  }
  
  return duration * 0.0343/2;
}
void setup(){
  scanner.attach(SERVO_PIN);
  
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.begin(9600);
  scanner.write(90);
  
}
void loop() {
  // scan from left to right
  for(int angle=0; angle <= 180 ; angle += 30) {
    scanner.write(angle);
    delay(300);
    
    distance = measureDistance();
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" | Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    if (distance > 0 && distance < STOP_DISTANCE) {
      Serial.println("OBSTACLE DETECTED! Scanning stopped.");
      while (true) {
        delay(100);
      }
    }
  }
}
