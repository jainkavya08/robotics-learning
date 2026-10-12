#define BUTTON 2
#define LED 13

int ledState = LOW;
int lastButtonState = HIGH;
int pressCount = 0;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
  digitalWrite(LED,ledState);
}

void loop() {
  int buttonState = digitalRead(BUTTON);
  if (lastButtonState == HIGH && buttonState == LOW) {
    ledState = !ledState;
    digitalWrite(LED, ledState);
    pressCount++;
    Serial.print("Button presses: ");
    Serial.println(pressCount);
    delay(50);
  }
    lastButtonState = buttonState;
}
