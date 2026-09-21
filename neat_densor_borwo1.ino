int LED1=10;
int LED2=9;
int LED3=6;
int LED4=5;
int LED5=3;
int POT=A0;
int potResolution=8;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(POT, INPUT);
}

void loop()
{
  int potValue=analogRead(POT);
  int cycle=map(potValue,0,1023,0,255);
  
  if (cycle==0) {
   	analogWrite(LED1,LOW);
   	analogWrite(LED2,LOW);
   	analogWrite(LED3,LOW);
   	analogWrite(LED4,LOW);
   	analogWrite(LED5,LOW);
  } else if (cycle>0&&cycle<=51) {
  	analogWrite(LED1,cycle);
  } else if (cycle>51&&cycle<=102) {
  	analogWrite(LED2,cycle);
  } else if (cycle>102&&cycle<=153) {
  	analogWrite(LED3,cycle);
  } else if (cycle>153&&cycle<=204) {
  	analogWrite(LED4,cycle);
  } else if (cycle>204&&cycle<=255) {
  	analogWrite(LED5,cycle);
  }
}