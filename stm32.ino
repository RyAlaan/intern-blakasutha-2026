//Kode program menyalakan led dan print hello world pada stm32

void setup() {
  
  pinMode (PC13,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(PC13,LOW);
  delay(500);

  digitalWrite(PC13,HIGH);
  delay(500);
  Serial.println("Hello, World!");
  delay(1000);
}
