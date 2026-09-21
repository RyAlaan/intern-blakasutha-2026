#include <Servo.h>
Servo MyServo;
int b1 = 7, b2 = 2;
int servo1 = 9;
int awal = 0;
const int step = 5;
const int jeda = 200;
//definisi input button 1, 2
//definisi pin servo
//definisi posisi awal servo, step, jeda

void setup() {
  MyServo.attach(servo1); //pin servo
  pinMode(b1, INPUT_PULLUP); // pin tombol 1
  pinMode(b2, INPUT_PULLUP); // pin tombol 2
  MyServo.write(awal); //posisi awal servo
}

void loop() {
  bool click1 = digitalRead(b1);
  bool click2 = digitalRead(b2);
  if(click1 == LOW) {
    if(awal < 180) {
      awal += step;
      MyServo.write(awal);
   	  delay(jeda);
    }
  }
  if(click2 == LOW) {
    if(awal > 0) {
      awal -= step;
      MyServo.write(awal);
   	  delay(jeda);
    }
  }
}
    
  
  