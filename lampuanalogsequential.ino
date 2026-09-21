int Pot = A0;
int Led[5] = {3, 5, 6, 9, 10};
#define PWM_FREQ 5000
#define PWM_LED 5


void setup() {
  pinMode(Pot, INPUT);
  pinMode(Led[0], OUTPUT);
  pinMode(Led[1], OUTPUT);
  pinMode(Led[2], OUTPUT);
  pinMode(Led[3], OUTPUT);
  pinMode(Led[4], OUTPUT);
}

void loop() {
  int PotVal = analogRead(Pot);
  int Converse = map(PotVal, 0, 1023, 0, 255); 
  if (Converse >= 0) analogWrite(Led[0], Converse);
  if(Converse >= 52) analogWrite(Led[1], Converse);
 	 else if(Converse <= 51) analogWrite(Led[1], 0);
  if(Converse >= 103) analogWrite(Led[2], Converse);
     else if(Converse <=102) analogWrite(Led[2], 0);
  if(Converse >= 154) analogWrite(Led[3], Converse);
     else if(Converse <=153) analogWrite(Led[3], 0);
  if(Converse >= 205) analogWrite(Led[4], Converse);
	 else if(Converse <=204) analogWrite(Led[4], 0);
}
  