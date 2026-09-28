#define PWM_FREQ 5000
#define PWM_RES 8

#define POTENSIO A0

int ledPin [5] = {9, 10, 11, 12, 13};

void setup(){
  for(int i=0; i < 5; i++){
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(POTENSIO, INPUT);
}

void loop(){
  int potensioValue = analogRead(POTENSIO);
  int mapValue = map(potensioValue, 0, 1023, 0, 255);
  
  for(int i=0; i < 5; i++){
    if (mapValue >= 51 * (i+1)){
    	digitalWrite(ledPin[i], HIGH);
    }else{
    	digitalWrite(ledPin[i], LOW);
    }          
  }
}
