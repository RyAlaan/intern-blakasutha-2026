void setup() {
  Serial.begin(115200);
  delay(1600);
}

void loop() {
  Serial.println("Hello World!");
  neopixelWrite(RGB_BUILTIN, 255, 0, 0);
  delay(400);
  neopixelWrite(RGB_BUILTIN, 0, 255, 0);
  delay(400);
  neopixelWrite(RGB_BUILTIN, 0 , 0, 255);
  delay(400);
}
