#include <Arduino.h>

void setup(){
  Serial.begin(115200);
  //Inisiasi Serial dengan kecepatan 115200
}

void loop(){
  Serial.println("Hello Dunia");
  //Mencetak tulisan "Hallo Dunia" pada serial Monitor
  delay(1000);
  neopixelWrite(RGB_BUILTIN, 255, 0, 0);
  //Menyalakan lampu builltin yang ada di esp32-s3
  delay(1000);
  neopixelWrite(RGB_BUILTIN, 0, 255, 0);
  delay(1000);
  neopixelWrite(RGB_BUILTIN, 0, 0, 255);
  delay(1000);
}
