#include "VCalc.h"

VCalc::VCalc(float _deadzone, float _speed) {
  this->_deadzone = _deadzone;
  this->_speed = _speed;
}

float VCalc::VxCalc(float x, float y) {
  if(sqrt(x*x + y*y) < _deadzone) return 0;
  else {
    float theta = atan2(y, x);
    return (_speed * cos(theta));
  }
}

float VCalc::VyCalc(float x, float y) {
  if(sqrt(x*x + y*y) < _deadzone) return 0;
  else {
    float theta = atan2(y, x);
    return (-(_speed * sin(theta)));
  }
}



