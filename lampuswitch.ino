int p1 = 7, p2 = 6, p3 = 5;
int b = 4;
bool state = 0;
bool laststate = 0;

void setup() {
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(b, INPUT_PULLUP);
}

void loop() {
  state = digitalRead(b); 
  if(state == 0) {
    laststate = !laststate;
  }
  if(laststate == 1) {
    digitalWrite(p1, HIGH);
  } else {
    digitalWrite(p1, LOW);
  }
  /*if(state == LOW) {
    digitalWrite(p1, HIGH);
  } else {
    digitalWrite(p1, LOW);
  } */
 /* digitalWrite(p2, HIGH);
  delay(2000);
  digitalWrite(p2, LOW);
  digitalWrite(p3, HIGH);
  delay(2000);
  digitalWrite(p3,LOW); */
}