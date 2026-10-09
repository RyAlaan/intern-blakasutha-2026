#include "SerialTransfer.h"

SerialTransfer myTransfer;

struct __attribute__((packed)) struct_message {
  int LX, LY, RX, RY;
  bool UP, DOWN, RIGHT, LEFT; 
} controllerData;

void setup() {
  Serial.begin(115200);  
  Serial1.begin(115200);  
  
  myTransfer.begin(Serial1);
  pinMode(PC13, OUTPUT);
}

void loop() {
  if(myTransfer.available()) {
    
    digitalWrite(PC13, LOW);  
    myTransfer.rxObj(controllerData, 0);
   
    Serial.print("LX: "); Serial.print(controllerData.LX);
    Serial.print(" | LY: "); Serial.print(controllerData.LY);
    Serial.print(" | RX: "); Serial.print(controllerData.RX);
    Serial.print(" | RY: "); Serial.print(controllerData.RY);

    //Serial.print(" || UP: "); Serial.print(controllerData.UP);
    //Serial.print(" | DOWN: "); Serial.print(controllerData.DOWN);
    //Serial.print(" | LEFT: "); Serial.print(controllerData.LEFT);
    //Serial.print(" | RIGHT: "); Serial.println(controllerData.RIGHT);

    digitalWrite(PC13, HIGH);
  }
}