#include<Servo.h>

#define SERVO_PIN 9

int leftButtonPin = 6;
int rightButtonPin = 8;

int position = 0;

Servo myServo;

void setup(){
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  myServo.attach(SERVO_PIN);
}

void loop(){
  int leftButtonValue = digitalRead(leftButtonPin);
  int rightButtonValue = digitalRead(rightButtonPin);
  
  if(leftButtonValue != LOW){
    if (position < -180){
    	position = -180;
    }
    for(int i=position; i > (position - 36); i--){
    	myServo.write(i);
      	delay(15);
    }
    position -= 36;
  }
  if(rightButtonValue != LOW){
  	if (position > 180){
    	position = 180;
    }
    for(int i=position; i < (position + 16); i++){
    	myServo.write(i);
      	delay(15);
    }
    
    position += 36;
  		
	}
}
                              
                            
                              
                              
             
