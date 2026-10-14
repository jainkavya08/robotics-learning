#define LED 9

void setup() {
	pinMode(LED,OUTPUT);
}

void loop() {
	analogWrite(LED,64);
}
