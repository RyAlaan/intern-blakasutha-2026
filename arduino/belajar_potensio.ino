#define PWM_FREQ 5000
#DEFINE PWM_RES 8

#define LED_PIN 5
#define POTENSIO A0

void setup(){
	pinMode(LED_PIN, OUTPUT);
  	pinMode(POTENSIO, INPUT);
}

void loop(){
	int potensioValue = analogRead(POTENSIO);
  	int mapValue = map(potensioValue, 0, 1023, 0, 255);
  
  	analogWrite(LED_PIN, mapValue);
}
