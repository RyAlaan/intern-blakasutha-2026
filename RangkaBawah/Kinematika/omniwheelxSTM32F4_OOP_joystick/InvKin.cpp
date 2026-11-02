#include "InvKin.h"

InvKin::InvKin(float _deadzone) {
  this->_deadzone = _deadzone;
}

float InvKin::InvKinW(float _alpha, float Vx, float Vy, float rspeed) {
  if(rspeed<_deadzone && rspeed>-_deadzone) rspeed = 0;
  return(Vx*(-sin(_alpha*DEG_TO_RAD)) + Vy*cos(_alpha*DEG_TO_RAD)) + (-(rspeed)); 
}
