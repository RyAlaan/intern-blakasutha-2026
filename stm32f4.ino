void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  neopixelWrite(PC13, LOW);
  delay(1000);
  digitalWrite(PC13, HIGH);
  delay(1000);
}