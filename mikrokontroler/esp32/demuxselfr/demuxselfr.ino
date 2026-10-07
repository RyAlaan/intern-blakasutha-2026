#define sel PA2
#define pwm PB8

void setup() {
  Serial.begin(115200);

  pinMode(sel, OUTPUT);
  pinMode(pwm, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {

    String input = Serial.readString();
    input.trim();

    if (input == "w" || input == "W") {
      digitalWrite(sel, HIGH);
      analogWrite(pwm, 200);
      delay(200);
    }

    else if (input == "a" || input == "A") {
      digitalWrite(sel, LOW);
      analogWrite(pwm, 200);
      delay(200);

    }

    else if (input == "s" || input == "S") {
      analogWrite(pwm, 0);
      delay(200);
    }
  }
}