#include <Arduino.h>

const int pin_l = PB8;
const int pin_r = PB9;

void setup() {
  Serial.begin(115200);
  pinMode(pin_r, OUTPUT);
  pinMode(pin_l, OUTPUT);
}

void loop() {
  if (Serial.available()) {

    String cmd = Serial.readString();
    cmd.trim(); 
    Serial.println(cmd);

      if ((cmd == "A" || cmd == "a")) {
        analogWrite(pin_r, 0);
        delay(1000);
        analogWrite(pin_l, 200);
        Serial.println("kiri");
      } else if ( (cmd == "S" || cmd == "s")) {
        analogWrite(pin_l, 0);
        delay(1000);
        analogWrite(pin_r, 200);
        Serial.println("kanan");
      } else if (cmd == "W" || cmd == "w") {
        analogWrite(pin_l, 0);
        analogWrite(pin_r, 0);
        Serial.println("stop");

  }
}
}
