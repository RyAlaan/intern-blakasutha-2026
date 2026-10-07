#include <Servo.h>

Servo myServo;

//definisi inputan
int btnknn = 2;
int btnkr  = 3;
int servo  = 9;

//posisi awal servo,step,jeda
 int awal = 90;
 int gerak= 5; 
const int jeda = 15;


void setup()
{
  myServo.attach(servo); //pin servo
  
  pinMode(btnknn,INPUT_PULLUP);
  pinMode(btnkr,INPUT_PULLUP);
  
  //set servo ke posisi awal
  myServo.write(awal);
}

void loop()
{
  //membaca input kedua tombol
  int statebtnknn = 2;
  int statebtnkr  = 3;
  
  
  //tombol kanan se arah jarum jam kelipatan gerak
  //tombol kiri sebalik arah jarum jam kelipatan gerak
  statebtnknn = digitalRead(btnknn);
  statebtnkr = digitalRead(btnkr);
  
  if (statebtnknn==LOW){
    awal-= 5;
    myServo.write(awal);
    delay(200);
  }
      
  if (statebtnkr==LOW){
    awal+= 5;
    myServo.write(awal);
    delay(200);
  }
}
  
  
  

  
