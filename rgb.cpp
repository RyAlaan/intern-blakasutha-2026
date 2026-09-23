#include <Arduino.h>

void setup(){
  Serial.begin(115200);
}

void loop(){
  Serial.println("Hello Dunia");
  delay(1000);
  neopixelWrite(RGB_BUILTIN, 255, 0, 0);
  delay(1000);
  neopixelWrite(RGB_BUILTIN, 0, 255, 0);
  delay(1000);
  neopixelWrite(RGB_BUILTIN, 0, 0, 255);
  delay(1000);
}
