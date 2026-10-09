#include <Arduino.h>

const int pin_r = PB9;
const int _sel = PA2;

bool running = false;

void setup() {
  Serial.begin(115200);
  pinMode(pin_r, OUTPUT);
  pinMode(_sel, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readString();
    cmd.trim();
    Serial.println(cmd);

    if (cmd == "A" || cmd == "a") {
      digitalWrite(_sel, HIGH);
      running = true;
      Serial.println("kiri");
    } else if (cmd == "S" || cmd == "s") {
      digitalWrite(_sel, LOW);
      running = true;
      Serial.println("kanan");
    } else if (cmd == "W" || cmd == "w") {
      running = false;
      analogWrite(pin_r, 0);
      Serial.println("stop");
    }
  }

  if (running) {
    analogWrite(pin_r, 200);
  }
}
