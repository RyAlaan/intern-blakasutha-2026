#include "SerialTransfer.h"

SerialTransfer myTransfer;


struct STRUCT {
  char z;
  float y;
} testStruct;


void setup()

{
  Serial.begin(115200);
  Serial1.begin(115200);
  myTransfer.begin(Serial1);
}


void loop()
{
  if(myTransfer.available())

  {
    uint16_t recSize = 0;

    recSize = myTransfer.rxObj(testStruct, recSize);
    Serial.print(testStruct.z);
    Serial.print(testStruct.y);
    Serial.print(" | ");

  }
}

