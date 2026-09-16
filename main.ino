int pin[3] = {7, 8, 13};

void setup(){
  for (int i = 0; i <= 3; i++){
    pinMode(pin[i], OUTPUT);
  }
}

void loop(){
  for (int i = 0; i <= 3; i++){
    digitalWrite(pin[i], HIGH);
    delay(2000);
    digitalWrite(pin[i], LOW);
    delay(500);
  }
}