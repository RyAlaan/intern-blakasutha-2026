
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
    Serial.printf("LX:%d LY:%d rX:%d rY:%d arUP:%d arDW:%d arRT:%d arLT:%d",
                  receivedData.LX,
                  receivedData.LY,
                  receivedData.rX,
                  receivedData.rY,
                  receivedData.arUp,
                  receivedData.arDw,
                  receivedData.arRt, );

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
