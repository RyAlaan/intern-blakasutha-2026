void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PC13, HIGH);
  delay(2000);
  digitalWrite(PC13, LOW);
  delay(2000);
}
