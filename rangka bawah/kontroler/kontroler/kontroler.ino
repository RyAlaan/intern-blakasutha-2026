#include <PS2X_lib.h>  


#define PS2_DAT        19  
#define PS2_CMD        23  
#define PS2_SEL         5  
#define PS2_CLK        18 

#define pressures   false
#define rumble      false

PS2X ps2x; 
int error = -1;
byte type = 0;
byte vibrate = 0;
int tryNum = 1;

void setup(){

 
  Serial.begin(115200);

 
  while (error != 0) {
    delay(1000);
    
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    Serial.print("#try config ");
    Serial.println(tryNum);
    tryNum ++;
  }

  Serial.println(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch(type) {
    case 0:
      Serial.println(" Unknown Controller type found ");
      break;
    case 1:
      Serial.println(" DualShock Controller found ");
      break;
    case 2:
      Serial.println(" GuitarHero Controller found ");
      break;
          case 3:
      Serial.println(" Wireless Sony DualShock Controller found ");
      break;
   }
}

void loop() {

  ps2x.read_gamepad(false, 0); 

  Serial.print("Stick Values:");
  Serial.print(ps2x.Analog(PSS_LY)); 
  Serial.print(",");
  Serial.print(ps2x.Analog(PSS_LX), DEC);
  Serial.print(",");
  Serial.print(ps2x.Analog(PSS_RY), DEC);
  Serial.print(",");
  Serial.println(ps2x.Analog(PSS_RX), DEC);
  delay(50);
}