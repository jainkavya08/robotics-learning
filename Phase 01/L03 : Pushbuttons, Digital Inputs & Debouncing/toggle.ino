#define LED 13
#define BUTTON 2 

int ledState = LOW;
int lastbuttonState = HIGH;

void setup(){
	pinMode(BUTTON, INPUT_PULLUP);
	pinMode(LED, OUTPUT);

	digitalWrite(LED, ledState);
}

void loop() {
	int buttonState = digitalRead(BUTTON);
	if(lastbuttonState == HIGH && buttonState == LOW);
	ledState =! ledState;
	digitalWrite(LED, ledState);
	delay(50); 
}
lastButtonState = ButtonState;
}

