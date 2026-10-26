#pragma once
#include <Arduino.h>

class RunRobot {
  public:
    int _pwm1, _sel1;
    int _pwm2, _sel2;
    int _pwm3, _sel3;
    int _pwm4, _sel4;
    float _speedlimit;
    RunRobot(int _pwm1, int _pwm2, int _pwm3, int _pwm4, int _sel1, int _sel2, int _sel3, int _sel4, float _speedlimit);
    void RunWheel(int _pwm, int _sel, float W);
    void RunRobotW(float W1, float W2, float W3, float W4);
};