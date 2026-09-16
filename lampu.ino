int p1 = 7, p2 = 6, p3 = 5;



void setup() {
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
}

void loop() {
  digitalWrite(p1, HIGH);
  delay(2000);
  digitalWrite(p2, HIGH);
  digitalWrite(p1, LOW);
  delay(2000);
  digitalWrite(p2, LOW);
  digitalWrite(p3, HIGH);
  delay(2000);
  digitalWrite(p3,LOW);
}