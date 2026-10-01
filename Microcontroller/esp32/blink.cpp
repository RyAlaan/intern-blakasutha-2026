#include<Arduino.h>

void setup(){
  pinMode(PC13, OUTPUT);
  //Inisiasi pin PC13 ke mode OUTPUT
}
void loop(){
  digitalWrite(PC13, HIGH);
  //Menyalakan lampu melalui pin 13
  delay(5000);
  digitalWrite(PC13, LOW);
  //Mematikan lampu melalui pin 13
  delay(1000);
}
