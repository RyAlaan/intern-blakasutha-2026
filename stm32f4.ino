void setup() {
  Serial.begin(9600); // komunikasi Serial dengan kecepatan transfer data 9600 bps
  pinMode(PC13, OUTPUT); // pin led (PC13)
}

void loop() {
  Serial.println("Hello World"); // mengirimkan teks "Hello World" ke Serial Monitor
  delay(500);  // jeda selama 500 milidetik
  digitalWrite(PC13, HIGH); //led menyala
  delay(100); // jeda selama 100 milidetik
  digitalWrite(PC13, LOW); //led mati
  delay(100); // jeda selama 100 milidetik
}