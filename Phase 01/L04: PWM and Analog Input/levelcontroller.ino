
#define LED 9
#define POT A0
int potValue = 0;
int brightness = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(POT);
  if (potValue < 300) {
    brightness = 0;
  } else if (potValue < 700) {
    brightness = 128;
  } else {
    brightness = 255;
  }
  analogWrite(LED, brightness);
  Serial.print("Sensor: ");
  Serial.print(potValue);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);
  delay(100);
}
