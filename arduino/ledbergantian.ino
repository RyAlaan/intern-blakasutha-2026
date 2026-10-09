int pin = 7;
int pin2 = 13;
int pin3 = 8;
int push = 4;
bool state = 0;
bool laststate = 0;

void setup()
{
  pinMode(pin, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(push, INPUT_PULLUP);
}

void loop(){
  state = digitalRead(push);
  if (state == 0) {
    laststate = !laststate;
  }
  if (state == 1) {
      digitalWrite(pin, LOW);
  } 
  else {
  	digitalWrite(pin, HIGH);
  }
}