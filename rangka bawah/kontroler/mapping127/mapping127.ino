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
int RX, RY;

// Mapping simetris dengan titik tengah 127/128 = 0
int mapStick(int raw) {
  raw = constrain(raw, 0, 255);

  if (raw <= 127) {
    return map(raw, 0, 127, -127, 0);
  } else {
    return map(raw, 128, 255, 0, 127);
  }
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
  rawRX = ps2x.Analog(PSS_RX);
  rawRY = ps2x.Analog(PSS_RY);

  // Mapping menjadi -127 sampai +127
  LX = mapStick(rawLX);
  LY = mapStick(rawLY);
  RX = mapStick(rawRX);
  RY = mapStick(rawRY);

  // Tampilkan raw dan hasil mapping
  Serial.printf(
    "LX: %3d -> %4d | LY: %3d -> %4d || "
    "RX: %3d -> %4d | RY: %3d -> %4d\n",
    rawLX, LX,
    rawLY, LY,
    rawRX, RX,
    rawRY, RY
  );

  delay(20);
}