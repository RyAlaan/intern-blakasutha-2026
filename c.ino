#include <Servo.h>
//DEFINISI PIN INPUTAN (BUUTON 1, 2), PIN SERVO (POSISI AWAL SERVO, STATE DAN JEDA)

Servo myServo;
int btnKir = 2;
int btnKan = 3;
int ServoPin = 9;

int awal = 90;
int step = 5;
const int jeda = 15;

void setup()
{
  myServo.attach(ServoPin); //pin servo
  pinMode(btnKan, INPUT_PULLUP);
  pinMode(btnKir, INPUT_PULLUP);
  
  myServo.write(awal); //kaya pinmode tapi buat servo set servo ke posisi awal
}

void loop()
{
  //membaca input kedua tombol
  int statebtnKir = 2;
  int statebtnKan = 3;

  statebtnKan = digitalRead(statebtnKan);
  statebtnKir = digitalRead(statebtnKir);
  if (statebtnKan == LOW){
  	awal -=5;
  	myServo.write(awal);
    delay (jeda);
  }
  if (statebtnKir == LOW) {
  	awal +=5;
  	myServo.write(awal);
    delay (jeda);
  }
}

