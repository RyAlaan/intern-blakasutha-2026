int pin1=13;
int pin2=9;
int pin3=7;

void setup(){
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
}

void loop(){
    digitalWrite(pin1, HIGH);
  	delay(1000);
  	digitalWrite(pin1, LOW);
   	digitalWrite(pin2, HIGH);
  	delay(1000);
  	digitalWrite(pin2, LOW);
  	digitalWrite(pin3, HIGH);
  	delay(1000);
  	digitalWrite(pin3, LOW);
 
}