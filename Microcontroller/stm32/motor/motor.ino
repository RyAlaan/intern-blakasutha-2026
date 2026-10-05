int r = PB9;
int l = PB8;
char input;

void setup() {
  Serial.begin(115200);
  pinMode(r, OUTPUT);
  pinMode(l, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char input=(char)Serial.read();
    if (input == 'w') {
      analogWrite(r, 0);
      analogWrite(l, 0);
      delay(100);
    } else if (input == 'a') {
      analogWrite(r, 0);
      analogWrite(l, 255);
      delay(100);
    } else if (input == 'd') {
      analogWrite(r, 255);
      analogWrite(l, 0);
      delay(100);
    }
  }
}