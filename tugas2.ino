// C++ code
//
#define POT_PIN A0
#define PWM_FREQ 5000
#define PWM_LED 5
#define LED_PIN 11
#define LED_PIN2 10
#define LED_PIN3 9
#define LED_PIN4 6
#define LED_PIN5 5




void setup()
{
  pinMode(LED_PIN,OUTPUT);
  pinMode(LED_PIN2,OUTPUT);
  pinMode(LED_PIN3,OUTPUT);
  pinMode(LED_PIN4,OUTPUT);
  pinMode(LED_PIN5,OUTPUT);
  
}

void loop()
{
  int POT_PINvalue = analogRead(POT_PIN);
  int DutyCyclevalue = map (POT_PINvalue,0, 1023, 0, 255);

  analogWrite(LED_PIN,DutyCyclevalue);
  
  if (DutyCyclevalue >0 && DutyCyclevalue <=51 )
    analogWrite(LED_PIN,DutyCyclevalue);
  if (DutyCyclevalue >52 && DutyCyclevalue <=102 )
    analogWrite(LED_PIN2,DutyCyclevalue);
      else if (DutyCyclevalue <102)
               analogWrite(LED_PIN2,0);
  if (DutyCyclevalue >102 && DutyCyclevalue <=153 )
    analogWrite(LED_PIN3,DutyCyclevalue);
      else if (DutyCyclevalue <153)
               analogWrite(LED_PIN3,0);
  if (DutyCyclevalue >153 && DutyCyclevalue <=204 )
    analogWrite(LED_PIN4,DutyCyclevalue);
      else if (DutyCyclevalue <204)
               analogWrite(LED_PIN4,0);
  if (DutyCyclevalue >153 && DutyCyclevalue <=255 )
    analogWrite(LED_PIN5,DutyCyclevalue);
      else if (DutyCyclevalue <255)
               analogWrite(LED_PIN5,0);
   
}
    