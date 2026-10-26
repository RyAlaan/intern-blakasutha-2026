#include "SerialTransfer.h"
#include "VCalc.h"
#include "InvKin.h"
#include "RunRobot.h"

#define _pwm1 PB8 //1 kanan depan
#define _sel1 PA2
#define _pwm2 PB7 //2 kiri depan
#define _sel2 PA3
#define _pwm3 PB6 //3 kiri belakang
#define _sel3 PA4
#define _pwm4 PB9 //4 kanan belakang
#define _sel4 PA5

SerialTransfer myTransfer;

struct __attribute__((packed)) struct_message {
  float Lx;
  float Ly;
  float Rx;
  float Ry;
  bool Up;
  bool Right;
  bool Left;
  bool Down;
} Joystick;

unsigned long LastInput = 0;
unsigned long LastPrint = 0;
#define _res 12
#define _freq 20000
#define _scaling ((1 << _res) / 256)
#define _speed  (115*_scaling)
#define _deadzone (10*_scaling)
#define _speedlimit (255*_scaling)
#define _a1 45
#define _a2 135
#define _a3 225
#define _a4 315

struct {
  float Lx;
  float Ly;
  float Vx;
  float Vy;
  float rspeed;
  float W1;
  float W2;
  float W3;
  float W4;
} Wheelie;

VCalc callVCalc(_deadzone, _speed);
InvKin callInvKin(_deadzone);
RunRobot callRunRobot(_pwm1, _pwm2, _pwm3, _pwm4, _sel1, _sel2, _sel3, _sel4, _speedlimit);

void setup() {
  analogWriteResolution(_res);
  analogWriteFrequency(_freq);
  Serial.begin(115200);
  Serial1.begin(115200);
  myTransfer.begin(Serial1);
  pinMode(_pwm1, OUTPUT);
  pinMode(_sel1, OUTPUT);
  pinMode(_pwm2, OUTPUT);
  pinMode(_sel2, OUTPUT);
  pinMode(_pwm3, OUTPUT);
  pinMode(_sel3, OUTPUT);
  pinMode(_pwm4, OUTPUT);
  pinMode(_sel4, OUTPUT);
}


void loop()
{
  //receive data
  if(myTransfer.available())
  {
    uint16_t recSize = 0;
    recSize = myTransfer.rxObj(Joystick, recSize);
    LastInput = millis();
  }
  //check connection
  if((millis() - LastInput) > 400) {
    callRunRobot.RunRobotW(0, 0, 0, 0);
    return;
  }
  //calculate
  Wheelie.Lx = (Joystick.Lx*_scaling);
  Wheelie.Ly = (Joystick.Ly*_scaling);
  Wheelie.rspeed = (Joystick.Rx*_scaling);
  Wheelie.Vx = callVCalc.VxCalc(Wheelie.Lx, Wheelie.Ly);
  Wheelie.Vy = callVCalc.VyCalc(Wheelie.Lx, Wheelie.Ly);
  Wheelie.W1 = callInvKin.InvKinW(_a1, Wheelie.Vx, Wheelie.Vy, Wheelie.rspeed);
  Wheelie.W2 = callInvKin.InvKinW(_a2, Wheelie.Vx, Wheelie.Vy, Wheelie.rspeed);
  Wheelie.W3 = callInvKin.InvKinW(_a3, Wheelie.Vx, Wheelie.Vy, Wheelie.rspeed);
  Wheelie.W4 = callInvKin.InvKinW(_a4, Wheelie.Vx, Wheelie.Vy, Wheelie.rspeed);
  //run
  callRunRobot.RunRobotW(Wheelie.W1, Wheelie.W2, Wheelie.W3, Wheelie.W4);
  //output
  if((millis() - LastPrint) >= 200) {
    LastPrint = millis();
    Serial.print(Wheelie.W1);
    Serial.print(" | ");
    Serial.print(Wheelie.W2);
    Serial.print(" | ");
    Serial.print(Wheelie.W3);
    Serial.print(" | ");
    Serial.println(Wheelie.W4);
  }
}
