#define pwm_1 PB6
#define pwm_2 PB7
#define pwm_3 PB8 
#define pwm_4 PB9 

#define sel_1 PA2
#define sel_2 PA3
#define sel_3 PA4
#define sel_4 PA5

void setup() {
  Serial.begin(115200);
  pinMode(pwm_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);
  pinMode(pwm_3, OUTPUT);
  pinMode(pwm_4, OUTPUT);
  pinMode(sel_1, OUTPUT);
  pinMode(sel_2, OUTPUT);
  pinMode(sel_3, OUTPUT);
  pinMode(sel_4, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == 'w' || input == 'W') {
      digitalWrite(sel_1, HIGH);
      analogWrite(pwm_1, 200);
      digitalWrite(sel_2, LOW);
      analogWrite(pwm_2, 200);
      digitalWrite(sel_3, LOW);
      analogWrite(pwm_3, 200);
      digitalWrite(sel_4, HIGH);
      analogWrite(pwm_4, 200);
      Serial.println("Maju");
    } 
    else if (input == 's' || input == 'S') {
      digitalWrite(sel_1, LOW);
      analogWrite(pwm_1, 200);
      digitalWrite(sel_2, HIGH);
      analogWrite(pwm_2, 200);
      digitalWrite(sel_3, HIGH);
      analogWrite(pwm_3, 200);
      digitalWrite(sel_4, LOW);
      analogWrite(pwm_4, 200);
      Serial.println("Mundur"); 
    } 
    else if (input == 'a' || input == 'A') {
      digitalWrite(sel_1, HIGH);
      analogWrite(pwm_1, 200);
      digitalWrite(sel_2, HIGH);
      analogWrite(pwm_2, 200);
      digitalWrite(sel_3, LOW);
      analogWrite(pwm_3, 200);
      digitalWrite(sel_4, LOW);
      analogWrite(pwm_4, 200);
      Serial.println("Kiri"); 
    }
    else if (input == 'd' || input == 'D') {
      digitalWrite(sel_1, LOW);
      analogWrite(pwm_1, 200);
      digitalWrite(sel_2, LOW);
      analogWrite(pwm_2, 200);
      digitalWrite(sel_3, HIGH);
      analogWrite(pwm_3, 200);
      digitalWrite(sel_4, HIGH);
      analogWrite(pwm_4, 200);
      Serial.println("Kanan");
    }
    else if (input == 'x' || input == 'X') {
     analogWrite(pwm_1, 0);
     analogWrite(pwm_2, 0);
     analogWrite(pwm_3, 0);
     analogWrite(pwm_4, 0);
     Serial.println("Berhenti");
    }
    else if (input == 'q'|| input == 'Q') {
      digitalWrite(sel_1, HIGH);
      analogWrite(pwm_1, 200);
      analogWrite(pwm_2, 0);
      digitalWrite(sel_3, LOW);
      analogWrite(pwm_3, 200);
      analogWrite(pwm_4, 0);
      Serial.println("Serong Kiri Atas"); 
    } 
    else if (input == 'e' || input == 'E') {
      analogWrite(pwm_1, 0);
      digitalWrite(sel_2, LOW);
      analogWrite(pwm_2, 200);
      analogWrite(pwm_3, 0);
      digitalWrite(sel_4, HIGH);
      analogWrite(pwm_4, 200);
      Serial.println("Serong Kanan Atas"); 
    }
    else if (input == 'z' || input == 'Z') {
      analogWrite(pwm_1, 0);
      digitalWrite(sel_2, HIGH);
      analogWrite(pwm_2, 200);
      analogWrite(pwm_3, 0);
      digitalWrite(sel_4, LOW);
      analogWrite(pwm_4, 200);
      Serial.println("Serong Kiri Bawah");
    }
    else if (input == 'c' || input == 'C') {
      digitalWrite(sel_1, LOW);
      analogWrite(pwm_1, 200);
      analogWrite(pwm_2, 0);
      digitalWrite(sel_3, HIGH);
      analogWrite(pwm_3, 200);
      analogWrite(pwm_4, 0);
      Serial.println("Serong Kanan Bawah");
    }
    delay(1000);
  }
}
