#define lpwm PB8
#define rpwm PB9
bool lpon = false;
bool rpon = false;
String input;
char move;

void setup() {
  Serial.begin(115200);
  pinMode(lpwm, OUTPUT);
  pinMode(rpwm, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    input = Serial.readStringUntil('\n');
    move = input[0];
  }
  if(move == 'a' && rpon == false) {
    analogWrite(rpwm, 0);
    analogWrite(lpwm, 100);
    lpon = true;
  } else if(move == 's' && lpon == false) {
    analogWrite(lpwm, 0);
    analogWrite(rpwm, 100);
    rpon = true;
  } else if(move == 'w') {
    analogWrite(lpwm, 0);
    analogWrite(rpwm, 0);
    lpon = false;
    rpon = false;
  }
  Serial.println(move);
  delay(1000);
}
