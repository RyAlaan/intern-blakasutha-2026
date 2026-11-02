#pragma once
#include <Arduino.h>

class InvKin {
  public:
    float _deadzone;
    InvKin(float _deadzone);
    float InvKinW(float alpha, float Vx, float Vy, float rspeed);
};