#include "SerialTransfer.h"


SerialTransfer myTransfer;

struct __attribute__((packed)) STRUCT {
  char z;
  float y;
} testStruct;

char arr[] = "abcde";

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(PC13, OUTPUT);
  myTransfer.begin(Serial1);

  testStruct.z = '$';
  testStruct.y = 4.5;
}


void loop()
{
  digitalWrite(PC13, HIGH); 
  delay(100); 
  digitalWrite(PC13, LOW); 
  delay(100); 
  uint16_t sendSize = 0;

  sendSize = myTransfer.txObj(testStruct, sendSize);

  sendSize = myTransfer.txObj(arr, sendSize);

  myTransfer.sendData(sendSize);
  delay(500);
}