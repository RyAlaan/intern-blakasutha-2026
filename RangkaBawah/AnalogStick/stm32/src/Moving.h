#pragma once
#include "Variable.h"

void move(float w1, float w2, float w3, float w4)
{
  // WHEEL 1
  if (w1 > 0)
  {
    Serial.println("Motor 1 CW");
    Serial.println(abs(w1));
    digitalWrite(mux_1, LOW);
    analogWrite(pwm_1, abs(w1));
  }
  else if (w1 < 0)
  {
    Serial.println("Motor 1 CCW");
    Serial.println(abs(w1));
    digitalWrite(mux_1, HIGH);
    analogWrite(pwm_1, abs(w1));
  }
  else
  {
    Serial.println("Motor 1 Stop");
    analogWrite(pwm_1, abs(w1));
  }
  // WHEEL 2
  if (w2 > 0)
  {
    Serial.println("Motor 2 CW");
    Serial.println(abs(w2));
    digitalWrite(mux_2, LOW);
    analogWrite(pwm_2, abs(w2));
  }
  else if (w2 < 0)
  {
    Serial.println("Motor 2 CCW");
    Serial.println(abs(w2));
    digitalWrite(mux_2, HIGH);
    analogWrite(pwm_2, abs(w2));
  }
  else
  {
    Serial.println("Motor 2 Stop");
    analogWrite(pwm_2, abs(w2));
  }
  // WHEEL 3
  if (w3 > 0)
  {
    Serial.println("Motor 3 CW");
    Serial.println(abs(w3));
    digitalWrite(mux_3, LOW);
    analogWrite(pwm_3, abs(w3));
  }
  else if (w3 < 0)
  {
    Serial.println("Motor 3 CCW");
    Serial.println(abs(w3));
    digitalWrite(mux_3, HIGH);
    analogWrite(pwm_3, abs(w3));
  }
  else
  {
    Serial.println("Motor 3 Stop");
    analogWrite(pwm_3, abs(w3));
  }
  // WHEEL 4
  if (w4 > 0)
  {
    Serial.println("Motor 4 CW");
    Serial.println(abs(w4));
    digitalWrite(mux_4, LOW);
    analogWrite(pwm_4, abs(w4));
  }
  else if (w4 < 0)
  {
    Serial.println("Motor 4 CCW");
    Serial.println(abs(w4));
    digitalWrite(mux_4, HIGH);
    analogWrite(pwm_4, abs(w4));
  }
  else
  {
    Serial.println("Motor 4 Stop");
    analogWrite(pwm_4, abs(w4));
  }
}