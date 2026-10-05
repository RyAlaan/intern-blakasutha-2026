#define _pwm PB9
#define _sel PA2

void setup() {
  Serial.begin(115200);
  pinMode(_pwm, OUTPUT);
  pinMode(_sel, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == 'a' || input == 'A') {
      digitalWrite(_sel, HIGH);
      analogWrite(_pwm, 200);
    } 
    else if (input == 's' || input == 'S') {
      digitalWrite(_sel, LOW);
      analogWrite(_pwm, 200);
    } 
    else if (input == 'w' || input == 'W') {
      analogWrite(_pwm, 0);
    }
    delay(1000);
  }
}



