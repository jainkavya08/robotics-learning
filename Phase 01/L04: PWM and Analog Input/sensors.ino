
#define LED 9
#define POT A0
int potValue = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(POT);
  if (potValue >= 512) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  Serial.println(potValue);
  delay(100);
}
