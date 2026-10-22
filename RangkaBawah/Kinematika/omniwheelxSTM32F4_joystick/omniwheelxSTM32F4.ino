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

unsigned long LastInput = 0;
unsigned long LastPrint = 0;
float scaling = 16;

struct {
  float W1;
  float W2;
  float W3;
  float W4;
} Wheelie;

float VxCalc(float y, float x) {
  if(sqrt(y*y + x*x) < 10) return 0;
  float theta = atan2(y, x);
  return ((115*scaling)*cos(theta)); 
}

float VyCalc(float y, float x) {
  if(sqrt(y*y + x*x) < 10) return 0;
  float theta = atan2(y, x);
  return -((115*scaling)*sin(theta));
}

float invkinematics(float alpha, float Vx, float Vy) {
  float Rotate;
  if(Joystick.Rx < 10 && Joystick.Rx > -10) Rotate = 0;
  else Rotate = -(Joystick.Rx);
  return((Vx*(-sin(alpha * DEG_TO_RAD)) + Vy*(cos(alpha * DEG_TO_RAD))) + (Rotate*scaling));
}

void runwheel(int _pwm, int _sel, float Wheel) {
  float CWheel = constrain(fabs(Wheel), 0, (255*scaling));
  if(Wheel > 0) {
    digitalWrite(_sel, HIGH);
    analogWrite(_pwm, CWheel);
  } else if(Wheel < 0) {
    digitalWrite(_sel, LOW);
    analogWrite(_pwm, CWheel);
  } else {
    analogWrite(_pwm, 0);
  }
}

void runrobot(float W1, float W2, float W3, float W4) {
  runwheel(_pwm1, _sel1, W1);
  runwheel(_pwm2, _sel2, W2);
  runwheel(_pwm3, _sel3, W3);
  runwheel(_pwm4, _sel4, W4);
}

void setup() {
  analogWriteResolution(12);
  analogWriteFrequency(20000);
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
    LastInput = millis();
  }
  //check connection
  if((millis() - LastInput) > 400) {
    runrobot(0, 0, 0, 0);
    return;
  }
  //calculate
  float Vx = VxCalc(Joystick.Ly, Joystick.Lx);
  float Vy = VyCalc(Joystick.Ly, Joystick.Lx);
  Wheelie.W1 = invkinematics(45, Vx, Vy);
  Wheelie.W2 = invkinematics(135, Vx, Vy);
  Wheelie.W3 = invkinematics(225, Vx, Vy);
  Wheelie.W4 = invkinematics(315, Vx, Vy);
  //run
  runrobot(Wheelie.W1, Wheelie.W2, Wheelie.W3, Wheelie.W4);
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

  // if(Joystick.Up==1) {
  //   digitalWrite(_sel1, HIGH);
  //   digitalWrite(_sel2, LOW);
  //   digitalWrite(_sel3, LOW);
  //   digitalWrite(_sel4, HIGH);
  //   analogWrite(_pwm1, speed);
  //   analogWrite(_pwm2, speed);
  //   analogWrite(_pwm3, speed);
  //   analogWrite(_pwm4, speed);
  // } else if (Joystick.Down==1) {
  //   digitalWrite(_sel1, LOW);
  //   digitalWrite(_sel2, HIGH);
  //   digitalWrite(_sel3, HIGH);
  //   digitalWrite(_sel4, LOW);
  //   analogWrite(_pwm1, speed);
  //   analogWrite(_pwm2, speed);
  //   analogWrite(_pwm3, speed);
  //   analogWrite(_pwm4, speed);
  // } else if(Joystick.Left==1) {
  //   digitalWrite(_sel1, HIGH);
  //   digitalWrite(_sel2, HIGH);
  //   digitalWrite(_sel3, LOW);
  //   digitalWrite(_sel4, LOW);
  //   analogWrite(_pwm1, speed);
  //   analogWrite(_pwm2, speed);
  //   analogWrite(_pwm3, speed);  
  //   analogWrite(_pwm4, speed);
  // } else if (Joystick.Right==1) {
  //   digitalWrite(_sel1, LOW);
  //   digitalWrite(_sel2, LOW);
  //   digitalWrite(_sel3, HIGH);
  //   digitalWrite(_sel4, HIGH);
  //   analogWrite(_pwm1, speed);
  //   analogWrite(_pwm2, speed);
  //   analogWrite(_pwm3, speed);
  //   analogWrite(_pwm4, speed);
  // } else {
  //   analogWrite(_pwm1, 0);
  //   analogWrite(_pwm2, 0);
  //   analogWrite(_pwm3, 0);
  //   analogWrite(_pwm4, 0);
  // }
  // Serial.print("Up: ");
  // Serial.println(Joystick.Up);
  // Serial.print("Right: ");
  // Serial.println(Joystick.Right);
  // Serial.print("Left: ");
  // Serial.println(Joystick.Left);
  // Serial.print("Down: ");
  // Serial.println(Joystick.Down);
}
