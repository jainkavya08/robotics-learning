#define LED 9 
#define POT AO

int potvalue = 0;
int brightness = 0;

void setup() {
	pinMode(LED,OUTPUT);
	Serial.begin(9600);
}

void loop() {
	potvalue = analogRead(POT);
	brightness = map(potvalue,0,1023,0,255);
	
	analogWrite(LED, brightness);

	Serial.print("Potentiometer: ");   
	Serial.print(potValue);   
	Serial.print(" | Brightness: ");   
	Serial.println(brightness);    

	delay(100);
	
}
