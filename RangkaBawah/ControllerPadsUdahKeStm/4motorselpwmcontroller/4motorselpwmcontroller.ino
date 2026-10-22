#include "SerialTransfer.h"

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

int speed = 100;

void setup()
{
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
  if(myTransfer.available())
  {
    uint16_t recSize = 0;
    recSize = myTransfer.rxObj(Joystick, recSize);
  }
  if(Joystick.Up==1) {
    digitalWrite(_sel1, HIGH);
    digitalWrite(_sel2, LOW);
    digitalWrite(_sel3, LOW);
    digitalWrite(_sel4, HIGH);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, speed);
  } else if (Joystick.Down==1) {
    digitalWrite(_sel1, LOW);
    digitalWrite(_sel2, HIGH);
    digitalWrite(_sel3, HIGH);
    digitalWrite(_sel4, LOW);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, speed);
  } else if(Joystick.Left==1) {
    digitalWrite(_sel1, HIGH);
    digitalWrite(_sel2, HIGH);
    digitalWrite(_sel3, LOW);
    digitalWrite(_sel4, LOW);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);  
    analogWrite(_pwm4, speed);
  } else if (Joystick.Right==1) {
    digitalWrite(_sel1, LOW);
    digitalWrite(_sel2, LOW);
    digitalWrite(_sel3, HIGH);
    digitalWrite(_sel4, HIGH);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, speed);
  } else {
    analogWrite(_pwm1, 0);
    analogWrite(_pwm2, 0);
    analogWrite(_pwm3, 0);
    analogWrite(_pwm4, 0);
  }
  Serial.print("Up: ");
  Serial.println(Joystick.Up);
  Serial.print("Right: ");
  Serial.println(Joystick.Right);
  Serial.print("Left: ");
  Serial.println(Joystick.Left);
  Serial.print("Down: ");
  Serial.println(Joystick.Down);
}
