#define pinr PB9
#define pinl PB8

void setup() {
  Serial.begin(115200);

  pinMode(pinr, OUTPUT);
  pinMode(pinl, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {

    String input = Serial.readString();
    input.trim();

    if (input == "w" || input == "W") {
      analogWrite(pinr, 0);
      analogWrite(pinl, 0);
      delay(200);
    }

    else if (input == "a" || input == "A") {
      analogWrite(pinr, 0);
      analogWrite(pinl, 255);
      delay(200);

    }

    else if (input == "s" || input == "S") {
      analogWrite(pinr, 255);
      analogWrite(pinl, 0);
      delay(200);
    }
  }
}