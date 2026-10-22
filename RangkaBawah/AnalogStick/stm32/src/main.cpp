#include "inverseKinematik.h"
#include "Normalize.h"
#include "Moving.h"
#include "Variable.h"

STRUCT receivedData;
SerialTransfer myTransfer;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  myTransfer.begin(Serial1);
  pinMode(pwm_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);
  pinMode(pwm_3, OUTPUT);
  pinMode(pwm_4, OUTPUT);

  pinMode(mux_1, OUTPUT);
  pinMode(mux_2, OUTPUT);
  pinMode(mux_3, OUTPUT);
  pinMode(mux_4, OUTPUT);

  analogWriteFrequency(20000);
  analogWriteResolution(12);
}

void loop()
{
  if (myTransfer.available())
  {
    uint16_t recSize = 0;

    recSize = myTransfer.rxObj(receivedData, recSize);
    int VxL = deadzone(mapJoystick(receivedData.LX));
    int VyL = deadzone(-mapJoystick(receivedData.LY));
    int R = deadzone(mapJoystick(receivedData.rX));

    if (VxL == 0 && VyL == 0 && R == 0)
    {
      move(0, 0, 0, 0);
    }
    else
    {

      float Rnorm = R / 127.0f;
      int Vx = 0;
      int Vy = 0;

      if (VxL != 0 || VyL != 0)
      {
        float theta = atan2((float)VyL, (float)VxL);
        Vx = SPEED * cos(theta);
        Vy = SPEED * sin(theta);
      }

      float W1 = inverseKinematik(Vx, Vy, Rnorm, 45);
      float W2 = inverseKinematik(Vx, Vy, Rnorm, 135);
      float W3 = inverseKinematik(Vx, Vy, Rnorm, 225);
      float W4 = inverseKinematik(Vx, Vy, Rnorm, 315);
      move(W1, W2, W3, W4);
    }
  }
}
