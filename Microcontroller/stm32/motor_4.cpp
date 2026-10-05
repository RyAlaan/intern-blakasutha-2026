#include <Arduino.h>

const int pwm_1 = PB6;
const int pwm_2 = PB7;
const int pwm_3 = PB8;
const int pwm_4 = PB9;

const int mux_1 = PA2;
const int mux_2 = PA3;
const int mux_3 = PA4;
const int mux_4 = PA5;

const int SPEED = 200;

void setMotors(int m1, int m2, int m3, int m4, int speed) {
  digitalWrite(mux_1, m1);
  digitalWrite(mux_2, m2);
  digitalWrite(mux_3, m3);
  digitalWrite(mux_4, m4);
  analogWrite(pwm_1, speed);
  analogWrite(pwm_2, speed);
  analogWrite(pwm_3, speed);
  analogWrite(pwm_4, speed);
}

void setup() {
  Serial.begin(115200);
  pinMode(pwm_1, OUTPUT); pinMode(pwm_2, OUTPUT);
  pinMode(pwm_3, OUTPUT); pinMode(pwm_4, OUTPUT);
  pinMode(mux_1, OUTPUT); pinMode(mux_2, OUTPUT);
  pinMode(mux_3, OUTPUT); pinMode(mux_4, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readString();
    cmd.trim();
    cmd.toUpperCase();

    if (cmd == "W")      { setMotors(HIGH, LOW, LOW, HIGH, SPEED); Serial.println("maju"); }
    else if (cmd == "S") { setMotors(LOW, HIGH, HIGH, LOW, SPEED); Serial.println("mundur"); }
    else if (cmd == "D") { setMotors(LOW, LOW, HIGH, HIGH, SPEED); Serial.println("kanan"); }
    else if (cmd == "A") { setMotors(HIGH, HIGH, LOW, LOW, SPEED); Serial.println("kiri"); }
    else if (cmd == "X") { setMotors(LOW, LOW, LOW, LOW, 0);       Serial.println("berhenti"); }
  }
}
