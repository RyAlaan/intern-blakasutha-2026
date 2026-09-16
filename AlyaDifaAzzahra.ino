int pin = 7;
int pin2 = 13;
int pin3 = 8;
void setup()
{
  pinMode(pin, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
}

void loop()
{
  digitalWrite(pin, HIGH);
  delay(2000); 
  digitalWrite(pin, LOW);
  delay(200); 
  digitalWrite(pin2, HIGH);
  delay(2000); 
  digitalWrite(pin2, LOW);
  delay(200); 
  digitalWrite(pin3, HIGH);
  delay(2000); 
  digitalWrite(pin3, LOW);
  delay(200);
}