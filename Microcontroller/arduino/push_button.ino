int led_1 = 7;
int led_2 = 8;
int led_3 = 13;
int button = 12;
bool state;
int last_state = HIGH;
void setup(){
  Serial.begin(115200);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop(){
  state = digitalRead(button);
  //Serial.println(state);
  if (state == LOW) {
    last_state = !last_state;
  }
  if (last_state == LOW) {
     digitalWrite(led_1, HIGH);
     digitalWrite(led_2, HIGH);
     digitalWrite(led_3, HIGH);
 
   // delay(50);
      } else
  {
     digitalWrite(led_1, LOW);
     digitalWrite(led_2, LOW);
     digitalWrite(led_3, LOW);

  }
}