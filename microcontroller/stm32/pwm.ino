#define pinrp PB9 
#define pinlp PB8

void setup() {
  Serial.begin(115200);
  pinMode(pinrp, OUTPUT);
  pinMode(pinlp, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim(); 

    if (input == "w" || input == "W") {
      analogWrite(pinrp, 0);   
      analogWrite(pinlp, 0);   
    } 
    else if (input == "s" || input == "S") {
      analogWrite(pinlp, 0);
      delay (1000);
      analogWrite(pinrp, 255);   
    } 
    else if (input == "a" || input == "A") {
      analogWrite(pinrp, 0);
      delay(1000);
      analogWrite(pinlp, 255); 
    } 
  }
}