int pin1=13;
int pin2=9;
int pin3=7;
int button=5;
bool isOn=false;

void setup(){
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop(){
  int state=digitalRead(button);
  
  if (state==LOW&&isOn==false) {
  	digitalWrite(pin1, HIGH);
    delay(500);
    isOn=true;
  } else if (state==LOW&&isOn==true) {
    digitalWrite(pin1, LOW);
    delay(500);
    isOn=false;  
  }

}