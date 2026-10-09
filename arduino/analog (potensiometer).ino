
#define POT_PIN A0
#define LED_PIN1 3
#define LED_PIN2 5
#define LED_PIN3 6
#define LED_PIN4 9
#define LED_PIN5 10
#define PWM_FREQ 5000
#define PWM_LED 5

void setup()
{
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  pinMode(LED_PIN5, OUTPUT);
  pinMode (POT_PIN, INPUT);
}

void loop()
{
  int POT_PINVALUE = analogRead (POT_PIN);
  int DutyCyclevalue = map (POT_PINVALUE, 0, 1023, 0, 255);
  
  if (DutyCyclevalue >0 && DutyCyclevalue <= 51)
    analogWrite (LED_PIN1, DutyCyclevalue);
  		else if (DutyCyclevalue <51)
       		analogWrite (LED_PIN1, 0);
  if (DutyCyclevalue >51 && DutyCyclevalue <= 102)
    analogWrite (LED_PIN2, DutyCyclevalue);
    	else if (DutyCyclevalue <102)
     		  analogWrite (LED_PIN2, 0);
  if (DutyCyclevalue >102 && DutyCyclevalue <= 153)
    analogWrite (LED_PIN3, DutyCyclevalue);
    	else if (DutyCyclevalue <153)
       		analogWrite (LED_PIN3, 0);
  if (DutyCyclevalue >153 && DutyCyclevalue <= 204)
    analogWrite (LED_PIN4, DutyCyclevalue);
    	else if (DutyCyclevalue <204)
      		analogWrite (LED_PIN4, 0);
  if (DutyCyclevalue >204 && DutyCyclevalue <= 255)
    analogWrite (LED_PIN5, DutyCyclevalue);
    	else if (DutyCyclevalue <255)
      		analogWrite (LED_PIN5, 0);
}