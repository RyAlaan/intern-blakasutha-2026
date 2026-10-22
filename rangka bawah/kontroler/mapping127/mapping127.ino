#include <PS2X_lib.h>

// Pin receiver PS2 ke ESP32
#define PS2_DAT 19
#define PS2_CMD 23
#define PS2_ATT 5
#define PS2_CLK 18

PS2X ps2x;

int error = 0;
byte controllerType = 0;

// Nilai analog asli dari stik PS2
int rawLX, rawLY;
int rawRX, rawRY;

// Hasil mapping -127 sampai +127
int LX, LY;
// int RX, RY;

//inverse kinematik
float IK(int x, int y, int alpha, int r){
  return (-sin(alpha*DEG_TO_RAD)*x)+(cos(alpha*DEG_TO_RAD)*y)+r;
}
// Mapping simetris dengan titik tengah 127/128 = 0
int mapStick(int raw, int center = 132) {
 
if (raw == center ) return 0;
if (raw < center) 
return map(raw, 0, center, -127, 0);
else return map (raw, center, 255, 0, 127);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("ESP32 - PS2 Controller");
  Serial.println("Menghubungkan stik PS2...");

  // CLK, CMD, ATT, DAT, pressures, rumble
  error = ps2x.config_gamepad(
    PS2_CLK,
    PS2_CMD,
    PS2_ATT,
    PS2_DAT,
    false,
    false
  );

  if (error == 0) {
    Serial.println("Stik PS2 berhasil terdeteksi!");
    controllerType = ps2x.readType();

    Serial.print("Tipe controller: ");
    Serial.println(controllerType);
  } else {
    Serial.print("Gagal mendeteksi stik PS2. Error: ");
    Serial.println(error);
    Serial.println("Periksa kabel dan pin, lalu reset ESP32.");
  }
}

void loop() {
  if (error != 0) {
    delay(1000);
    return;
  }

  // Membaca data terbaru dari stik
  ps2x.read_gamepad(false, 0);

  // Membaca nilai raw analog stick (0-255)
  rawLX = ps2x.Analog(PSS_LX);
  rawLY = ps2x.Analog(PSS_LY);
  // rawRX = ps2x.Analog(PSS_RX);
  // rawRY = ps2x.Analog(PSS_RY);

  // Mapping menjadi -127 sampai +127
  LX = mapStick(rawLX);
  LY = -mapStick(rawLY);
  // RX = mapStick(rawRX);
  // RY = mapStick(rawRY);

  // Tampilkan raw dan hasil mapping
  Serial.printf(
    "LX: %3d -> %4d | LY: %3d -> %4d |\n ",
    // "RX: %3d -> %4d | RY: %3d -> %4d\n",
    rawLX, LX,
    rawLY, LY
    // rawRX, RX,
    // rawRY, RY
     );
  float theta = atan2((float)LY, (float)LX);
    int Vx = 0;
    int Vy = 0;
     if (LX != 0 || LY != 0) {
         Vx = (int)(115 * cos(theta));
         Vy = (int)(115 * sin(theta));
  } 
  float w1 = IK(Vx,Vy,(45),0);
  float w2 = IK(Vx,Vy,(135),0);
  float w3 = IK(Vx,Vy,(225),0);
  float w4 = IK(Vx,Vy,(315),0);

  Serial.printf("Vx: %d, Vy: %d\n", Vx, Vy);
  Serial.printf("w1: %.2f,w2: %.2f,w3: %.2f,w4: %.2f\n", w1,w2,w3,w4);
 delay(50);
}
