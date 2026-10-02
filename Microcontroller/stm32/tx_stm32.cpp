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

  testStruct.z = 'hello bung';
  testStruct.y = 4.5;
}


void loop()
{
  uint16_t sendSize = 0;
  sendSize = myTransfer.txObj(testStruct, sendSize);
  myTransfer.sendData(sendSize);
  delay(500);
}
