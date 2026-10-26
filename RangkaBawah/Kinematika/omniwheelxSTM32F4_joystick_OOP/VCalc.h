#pragma once
#include <Arduino.h>

class VCalc{
  public: 
    float _deadzone;
    float _speed;
    VCalc(float _deadzone, float _speed);
    float VxCalc(float x, float y);
    float VyCalc(float x, float y);
};