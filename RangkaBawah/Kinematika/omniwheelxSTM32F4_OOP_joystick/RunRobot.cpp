#include "RunRobot.h"

RunRobot::RunRobot(int _pwm1, int _pwm2, int _pwm3, int _pwm4, int _sel1, int _sel2, int _sel3, int _sel4, float _speedlimit) {
  this->_pwm1 = _pwm1; this->_sel1 = _sel1;
  this->_pwm2 = _pwm2; this->_sel2 = _sel2;
  this->_pwm3 = _pwm3; this->_sel3 = _sel3;
  this->_pwm4 = _pwm4; this->_sel4 = _sel4;
  this->_speedlimit = _speedlimit;
}

void RunRobot::RunWheel(int _pwm, int _sel, float W) {
  float CW = constrain(fabs(W), 0, _speedlimit);
  if(W > 0) {
    digitalWrite(_sel, HIGH);
    analogWrite(_pwm, CW);
  } else if(W < 0) {
    digitalWrite(_sel, LOW);
    analogWrite(_pwm, CW);
  } else {
    analogWrite(_pwm, 0);
  }
}

void RunRobot::RunRobotW(float W1, float W2, float W3, float W4) {
  RunWheel(_pwm1, _sel1, W1);
  RunWheel(_pwm2, _sel2, W2);
  RunWheel(_pwm3, _sel3, W3);
  RunWheel(_pwm4, _sel4, W4);
}