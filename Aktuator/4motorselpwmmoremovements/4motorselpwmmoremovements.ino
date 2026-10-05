#define _pwm1 PB8 //1 kanan depan
#define _sel1 PA2
#define _pwm2 PB7 //2 kiri depan
#define _sel2 PA3
#define _pwm3 PB6 //3 kiri belakang
#define _sel3 PA4
#define _pwm4 PB9 //4 kanan belakang
#define _sel4 PA5
//HIGH = CCW
//LOW = CW
String input;
char move;
int speed = 100;
bool moving = false;

void setup() {
  Serial.begin(115200);
  pinMode(_pwm1, OUTPUT);
  pinMode(_sel1, OUTPUT);
  pinMode(_pwm2, OUTPUT);
  pinMode(_sel2, OUTPUT);
  pinMode(_pwm3, OUTPUT);
  pinMode(_sel3, OUTPUT);
  pinMode(_pwm4, OUTPUT);
  pinMode(_sel4, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    input = Serial.readStringUntil('\n');
    move = input[0];
  }
  if(move == 'w' && moving == false) {
    digitalWrite(_sel1, HIGH);
    digitalWrite(_sel2, LOW);
    digitalWrite(_sel3, LOW);
    digitalWrite(_sel4, HIGH);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, speed);
    moving = true;
  } else if (move == 's' && moving == false) {
    digitalWrite(_sel1, LOW);
    digitalWrite(_sel2, HIGH);
    digitalWrite(_sel3, HIGH);
    digitalWrite(_sel4, LOW);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, speed);
    moving = true;
  } else if(move == 'a' && moving == false) {
    digitalWrite(_sel1, HIGH);
    digitalWrite(_sel2, HIGH);
    digitalWrite(_sel3, LOW);
    digitalWrite(_sel4, LOW);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);  
    analogWrite(_pwm4, speed);
    moving = true;
  } else if (move == 'd' && moving == false) {
    digitalWrite(_sel1, LOW);
    digitalWrite(_sel2, LOW);
    digitalWrite(_sel3, HIGH);
    digitalWrite(_sel4, HIGH);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, speed);
    moving = true;
  } else if (move == 'e' && moving == false) {
    digitalWrite(_sel2, LOW);
    digitalWrite(_sel4, HIGH);
    analogWrite(_pwm1, 0);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, 0);
    analogWrite(_pwm4, speed);
    moving = true;
  } else if (move == 'q' && moving == false) {
    digitalWrite(_sel1, HIGH);
    digitalWrite(_sel3, LOW);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, 0);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, 0);
    moving = true;
  } else if (move == 'z' && moving == false) {
    digitalWrite(_sel2, HIGH);
    digitalWrite(_sel4, LOW);
    analogWrite(_pwm1, 0);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, 0);
    analogWrite(_pwm4, speed);
    moving = true;
  } else if (move == 'c' && moving == false) {
    digitalWrite(_sel1, LOW);
    digitalWrite(_sel3, HIGH);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, 0);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, 0);
    moving = true;
  } else if (move == 'j' && moving == false) {
    digitalWrite(_sel1, LOW);
    digitalWrite(_sel2, LOW);
    digitalWrite(_sel3, LOW);
    digitalWrite(_sel4, LOW);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, speed);
    moving = true;
  } else if (move == 'k' && moving == false) {
    digitalWrite(_sel1, HIGH);
    digitalWrite(_sel2, HIGH);
    digitalWrite(_sel3, HIGH);
    digitalWrite(_sel4, HIGH);
    analogWrite(_pwm1, speed);
    analogWrite(_pwm2, speed);
    analogWrite(_pwm3, speed);
    analogWrite(_pwm4, speed);
    moving = true;
  } else if (move == 'x' && moving == true) {
    analogWrite(_pwm1, 0);
    analogWrite(_pwm2, 0);
    analogWrite(_pwm3, 0);
    analogWrite(_pwm4, 0);
    moving = false;
  } 
  /*if (move == 'e' && moving == false) {
    digitalWrite(_sel4, HIGH);
    analogWrite(_pwm4, speed);
    moving = true;
  } else if (move == 'q' && moving == false) {
    digitalWrite(_sel4, LOW);
    analogWrite(_pwm4, speed);
    moving = true;
  } else if (move == 'x' && moving == true) {
    analogWrite(_pwm4, 0);
    moving = false;
  } */
  Serial.println(move);
  delay(400);
}
