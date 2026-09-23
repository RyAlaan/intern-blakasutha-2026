void setup() {
  pinMode(PC13, OUTPUT);
  Serial.begin(115200);
  delay(1600);
}

void loop() {
  Serial.println("Hello World!");
  digitalWrite(PC13, LOW);
  delay(400);
  digitalWrite(PC13, HIGH);
  delay(400);
}
