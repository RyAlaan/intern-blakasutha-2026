const int totalPin = 3;
int ledPin[totalPin] = {7, 9, 11};
int pinPos = 0;

void setup(){
    for(int i=0; i < totalPin; i++){
        pinMode(ledPin[i], OUTPUT);
    }
}

void loop(){
    digitalWrite(ledPin[pinPos], HIGH);
    pinPos++;
    if(pinPos >= totalPin){
        totalPin = 0;    
    }    
    delay(2000);
    digitalWrite(ledPin[pinPos); LOW);    
}
