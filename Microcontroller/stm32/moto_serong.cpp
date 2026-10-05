#include <Arduino.h>

const int pwm_1 = PB6;
const int pwm_2 = PB7;
const int pwm_3 = PB8;
const int pwm_4 = PB9;

//DEMUX
const int mux_1 = PA2;
const int mux_2 = PA3;
const int mux_3 = PA4;
const int mux_4 = PA5;

bool running = false;

void setup() {
  Serial.begin(115200);
  pinMode(pwm_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);
  pinMode(pwm_3, OUTPUT);
  pinMode(pwm_4, OUTPUT);

  pinMode(mux_1, OUTPUT);
  pinMode(mux_2, OUTPUT);
  pinMode(mux_3, OUTPUT);
  pinMode(mux_4, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readString();
    cmd.trim();
    Serial.println(cmd);


    if (cmd == "W" || cmd == "w") {
      running = false;
      analogWrite(mux_1, HIGH);
      analogWrite(mux_2, LOW);
      analogWrite(mux_3, LOW);
      analogWrite(mux_4, HIGH);

      analogWrite(pwm_1, 200);
      analogWrite(pwm_3, 200);
      analogWrite(pwm_2, 200);
      analogWrite(pwm_4, 200);

      Serial.println("maju");
    }  else if (cmd == "S" || cmd == "s") {
      analogWrite(mux_1, LOW);
      analogWrite(mux_2, HIGH);
      analogWrite(mux_3, HIGH);
      analogWrite(mux_4, LOW);

      analogWrite(pwm_1, 200);
      analogWrite(pwm_3, 200);
      analogWrite(pwm_2, 200);
      analogWrite(pwm_4,200);
      Serial.println("mundur");
    } else if (cmd == "D" || cmd == "d") {
      analogWrite(mux_1, LOW);
      analogWrite(mux_2, LOW);
      analogWrite(mux_3, HIGH);
      analogWrite(mux_4, HIGH);

      analogWrite(pwm_1, 200);
      analogWrite(pwm_3, 200);
      analogWrite(pwm_2, 200);
      analogWrite(pwm_4, 200);

      Serial.println("kanan");
    } else if (cmd == "A" || cmd == "a") {
      analogWrite(mux_1, HIGH);
      analogWrite(mux_2, HIGH);
      analogWrite(mux_3, LOW);
      analogWrite(mux_4, LOW);

      analogWrite(pwm_1, 200);
      analogWrite(pwm_3, 200);
      analogWrite(pwm_2, 200);
      analogWrite(pwm_4, 200);

      Serial.println("kiri");
    }  else if (cmd == "Q" || cmd == "q") {
      analogWrite(mux_1, HIGH);
   //   analogWrite(mux_2, HIGH);
      analogWrite(mux_3, LOW);
    //  analogWrite(mux_4, LOW);

      analogWrite(pwm_1, 200);
      analogWrite(pwm_3, 200);
      analogWrite(pwm_2, 0);
      analogWrite(pwm_4, 0);


      Serial.println("Kiri atas");
    } else if (cmd == "E" || cmd == "e") {
    //  analogWrite(mux_1, LOW);
      analogWrite(mux_2, LOW);
     // analogWrite(mux_3, HIGH);
      analogWrite(mux_4, HIGH);

      analogWrite(pwm_1, 0);
      analogWrite(pwm_3, 0);
      analogWrite(pwm_2, 200);
      analogWrite(pwm_4, 200);

      Serial.println("Kanan atas");
    } else if (cmd == "Z" || cmd == "z") {
    //  analogWrite(mux_1, HIGH);
      analogWrite(mux_2, HIGH);
    //  analogWrite(mux_3, LOW);
      analogWrite(mux_4, LOW);

      analogWrite(pwm_1, 0);
      analogWrite(pwm_3, 0);
      analogWrite(pwm_2, 200);
      analogWrite(pwm_4, 200);

      Serial.println("Kiri bawah");
    } 
    else if (cmd == "C" || cmd == "c") {
      analogWrite(mux_1, LOW);
   //   analogWrite(mux_2, LOW);
      analogWrite(mux_3, HIGH);
    //  analogWrite(mux_4, HIGH);

      analogWrite(pwm_1, 200);
      analogWrite(pwm_3, 200);
      analogWrite(pwm_2, 0);
      analogWrite(pwm_4, 0);

      Serial.println("Kanan bawah");
    } 
    else if (cmd == "X" || cmd == "x") {
      analogWrite(pwm_1, 0);
      analogWrite(pwm_2, 0);
      analogWrite(pwm_3, 0);
      analogWrite(pwm_4, 0);
      Serial.println("berhenti");
    }
  }


}
