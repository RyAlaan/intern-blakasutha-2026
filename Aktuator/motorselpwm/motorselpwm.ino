#define _pwm PB9
#define _sel PA2
String input;
char move;
int value = 100;
bool lon = false;
bool ron = false;


void setup() {
  Serial.begin(115200);
  pinMode(_pwm, OUTPUT);
  pinMode(_sel, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    input = Serial.readStringUntil('\n');
    move = input[0];
  }
  if(move == 'a' && ron == false) {
    digitalWrite(_sel, HIGH);
    analogWrite(_pwm, value);
    lon = true;
  } else if(move == 's' && lon == false) {
    digitalWrite(_sel, LOW);
    analogWrite(_pwm, value);
    ron = true;
  } else if(move == 'w') {
    analogWrite(_pwm, 0);
    lon = false;
    ron = false;
  }
  Serial.println(move);
  delay(500);
}
