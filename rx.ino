//A10
#include "SerialTransfer.h"

SerialTransfer myTransfer; 

struct __attribute__((packed)) STRUCT {
  char z;
  float y;
} testStruct;

char arr[6];

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  myTransfer.begin(Serial1);
  pinMode(PC13, OUTPUT);
}


void loop()
{
  if(myTransfer.available())
  {
    digitalWrite(PC13, HIGH); 
    delay(100); 
    digitalWrite(PC13, LOW); 
    delay(100); 
    uint16_t recSize = 0;

    recSize = myTransfer.rxObj(testStruct, recSize);
    Serial.print(testStruct.z);
    Serial.print(testStruct.y);
    Serial.print(" | ");

    recSize = myTransfer.rxObj(arr, recSize);
    Serial.println(arr);
  }
}