
#include "SerialTransfer.h"

SerialTransfer myTransfer;

const int pwm_1 = PB6;
const int pwm_2 = PB7;
const int pwm_3 = PB8;
const int pwm_4 = PB9;

const int mux_1 = PA2;
const int mux_2 = PA3;
const int mux_3 = PA4;
const int mux_4 = PA5;

struct STRUCT
{
  int LY, LX, rX, rY;
  bool arUp, arDw, arRt, arLt;
} receivedData;

const int SPEED = 2048;

float inverseKinematik(int x, int y, int r, int sudut)
{
  return ((-x * sin(sudut * DEG_TO_RAD)) + (y * cos(sudut * DEG_TO_RAD)) + r);
}
int deadzone(int val, int threshold = 10)
{
  return abs(val) < threshold ? 0 : val;
}

int mapJoystick(int raw, int center = 132)
{
  if (raw == center)
    return 0;
  if (raw < center)
    return map(raw, 0, center, -127, 0);
  else
    return map(raw, center, 255, 0, 127);
}
void setMotors(int m1, int m2, int m3, int m4, int speed)
{
  digitalWrite(mux_1, m1);
  digitalWrite(mux_2, m2);
  digitalWrite(mux_3, m3);
  digitalWrite(mux_4, m4);
  analogWrite(pwm_1, speed);
  analogWrite(pwm_2, speed);
  analogWrite(pwm_3, speed);
  analogWrite(pwm_4, speed);
}
void move(float w1, float w2, float w3, float w4)
{
  //WHEEL 1
  if (w1 > 0)
  {
    Serial.println("Motor 1 CW");
    Serial.println(abs(w1));
    digitalWrite(mux_1, LOW);
    analogWrite(pwm_1, abs(w1));
  }
  else if (w1 < 0)
  {
    Serial.println("Motor 1 CCW");
    Serial.println(abs(w1));
    digitalWrite(mux_1, HIGH);
    analogWrite(pwm_1, abs(w1));
  }
  else
  {
    Serial.println("Motor 1 Stop");
    analogWrite(pwm_1, abs(w1));
  }
  //WHEEL 2
  if (w2 > 0)
  {
    Serial.println("Motor 2 CW");
    Serial.println(abs(w2));
    digitalWrite(mux_2, LOW);
    analogWrite(pwm_2, abs(w2));
  }
  else if (w2 < 0)
  {
    Serial.println("Motor 2 CCW");
    Serial.println(abs(w2));
    digitalWrite(mux_2, HIGH);
    analogWrite(pwm_2, abs(w2));
  }
  else
  {
    Serial.println("Motor 2 Stop");
    analogWrite(pwm_2, abs(w2));
  }
  //WHEEL 3
  if (w3 > 0)
  {
    Serial.println("Motor 3 CW");
    Serial.println(abs(w3));
    digitalWrite(mux_3, LOW);
    analogWrite(pwm_3, abs(w3));
  }
  else if (w3 < 0)
  {
    Serial.println("Motor 3 CCW");
    Serial.println(abs(w3));
    digitalWrite(mux_3, HIGH);
    analogWrite(pwm_3, abs(w3));
  }
  else
  {
    Serial.println("Motor 3 Stop");
    analogWrite(pwm_3, abs(w3));
  }
  //WHEEL 4
  if (w4 > 0)
  {
    Serial.println("Motor 4 CW");
    Serial.println(abs(w4));
    digitalWrite(mux_4, LOW);
    analogWrite(pwm_4, abs(w4));
  }
  else if (w4 < 0)
  {
    Serial.println("Motor 4 CCW");
    Serial.println(abs(w4));
    digitalWrite(mux_4, HIGH);
    analogWrite(pwm_4, abs(w4));
  }
  else
  {
    Serial.println("Motor 4 Stop");
    analogWrite(pwm_4, abs(w4));
  }
}

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
    /*     Serial.printf("LX:%d LY:%d rX:%d rY:%d arUP:%d arDW:%d arRT:%d arLT:%d",
                      receivedData.LX,
                      receivedData.LY,
                      receivedData.rX,
                      receivedData.rY,
                      receivedData.arUp,
                      receivedData.arDw,
                      receivedData.arRt,
                      receivedData.arLt); */
    if (receivedData.LX == 0 && receivedData.LY == 0)
    {
      move(0, 0, 0, 0);
    }
    else
    {
      int VxL = deadzone(mapJoystick(receivedData.LX));
      int VyL = deadzone(-mapJoystick(receivedData.LY));
      int R = deadzone(mapJoystick(receivedData.rX));

      float theta = atan2((float)VyL, (float)VxL);
      int Vx = SPEED * cos(theta);
      int Vy = SPEED * sin(theta);

      float W1 = inverseKinematik(Vx, Vy, R, 45);
      float W2 = inverseKinematik(Vx, Vy, R, 135);
      float W3 = inverseKinematik(Vx, Vy, R, 225);
      float W4 = inverseKinematik(Vx, Vy, R, 315);
      move(W1, W2, W3, W4);
    }

    if (receivedData.arUp)
    {
      setMotors(HIGH, LOW, LOW, HIGH, SPEED);
      Serial.println("maju");
    }
    else if (receivedData.arDw)
    {
      setMotors(LOW, HIGH, HIGH, LOW, SPEED);
      Serial.println("mundur");
    }
    else if (receivedData.arRt)
    {
      setMotors(LOW, LOW, HIGH, HIGH, SPEED);
      Serial.println("kanan");
    }
    else if (receivedData.arLt)
    {
      setMotors(HIGH, HIGH, LOW, LOW, SPEED);
      Serial.println("kiri");
    }
    else
    {
      setMotors(LOW, LOW, LOW, LOW, 0);
      Serial.println("berhenti");
    }
  }
}
