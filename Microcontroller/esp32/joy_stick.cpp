#include <PS2X_lib.h>  //for v1.6


PS2X ps2x; // create PS2 Controller Class
int error = -1;
byte type = 0;

void setup(){

 // 115200
  Serial.begin(115200);

  int tryNum = 0;
  while (error != 0 && tryNum < 5) {
    delay(500);
    error = ps2x.config_gamepad(18, 23, 5, 19, false, false);
    Serial.printf("PS2 try %d: error=%d\n", ++tryNum, error);
  }

  if (error != 0) {
    Serial.println("PS2 gagal konek, cek wiring!");
    // Tetap lanjut, tidak return — supaya bisa debug
  } else {
    type = ps2x.readType();
    Serial.printf("PS2 type: %d\n", type);
  }


  Serial.println(ps2x.Analog(1), HEX);

}

void loop() {


    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY)); //Left stick, Y axis. Other options: LX, RY, RX
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC);
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC);
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC);
    }

  delay(50);
}
