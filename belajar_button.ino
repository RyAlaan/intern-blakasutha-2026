const int totalPin = 4;
int ledPin[totalPin] = {7, 9, 11, 13};
int buttonPin = 3;
int pinPos = 0;
bool buttonState;

void setup(){
  for(int i=0; i < totalPin; i++){
  	pinMode(ledPin[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop(){
  
  digitalWrite(ledPin[pinPos], HIGH);
  buttonState = digitalRead(buttonPin);
  
  if(buttonState){
    digitalWrite(ledPin[pinPos], LOW);
    pinPos += 1;
  }
  
  if(pinPos >= totalPin){
  	pinPos = 0;
  }
  delay(500);
}
