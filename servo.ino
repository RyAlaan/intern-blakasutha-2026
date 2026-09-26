#include <Servo.h>

Servo myServo;

int buttonLeft=2;
int buttonRight=3;
int servo=13;

int posisiAwal=90;
int rotasiPerputaran=10;
int rotasiJeda=200;

void setup()
{
  myServo.attach(servo);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  myServo.write(posisiAwal);
}

void loop()
{
  int stateButtonLeft=digitalRead(buttonLeft);
  int stateButtonRight=digitalRead(buttonRight);
  
  if (stateButtonLeft==LOW) {
  	posisiAwal-= rotasiPerputaran;
    myServo.write(posisiAwal);
    delay(rotasiJeda);
  }
  
  if (stateButtonRight==LOW) {
  	posisiAwal+= rotasiPerputaran;
    myServo.write(posisiAwal);
    delay(rotasiPerputaran);
  }
}