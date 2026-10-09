#include <WiFi.h>
#include <esp_now.h>
#include <PS2X_lib.h>

#define PS2_DAT 19
#define PS2_CMD 23
#define PS2_SEL 5
#define PS2_CLK 18

#define pressures false
#define rumble false

PS2X ps2x;
int error = -1;
int tryNum = 1;

uint8_t rxMAC[] = {
  0x68, 0xEE, 0x8F, 0x4F, 0x04, 0x1C
};

// Satu struktur, satu paket
typedef struct __attribute__((packed)) {
  uint8_t ly;
  uint8_t lx;
  uint8_t ry;
  uint8_t rx;

  uint8_t dpadUp;
  uint8_t dpadDown;
  uint8_t dpadLeft;
  uint8_t dpadRight;
} JoystickPacket;

JoystickPacket joystick;

void setup() {
  Serial.begin(115200);

  while (error != 0) {
    delay(1000);
    error = ps2x.config_gamepad(
      PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT,
      pressures, rumble
    );

    Serial.print("#try config ");
    Serial.println(tryNum++);
  }

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Error");
    while (true) delay(1000);
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, rxMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Gagal menambahkan RX");
    while (true) delay(1000);
  }

  Serial.println("TX siap!");
}

void loop() {
  ps2x.read_gamepad(false, 0);

  // Analog joystick
  joystick.ly = ps2x.Analog(PSS_LY);
  joystick.lx = ps2x.Analog(PSS_LX);
  joystick.ry = ps2x.Analog(PSS_RY);
  joystick.rx = ps2x.Analog(PSS_RX);

  // D-pad: 1 jika ditekan, 0 jika tidak
  joystick.dpadUp =
    ps2x.Button(PSB_PAD_UP) ? 1 : 0;

  joystick.dpadDown =
    ps2x.Button(PSB_PAD_DOWN) ? 1 : 0;

  joystick.dpadLeft =
    ps2x.Button(PSB_PAD_LEFT) ? 1 : 0;

  joystick.dpadRight =
    ps2x.Button(PSB_PAD_RIGHT) ? 1 : 0;

  // Kirim semua data dalam satu paket
  esp_err_t result = esp_now_send(
    rxMAC,
    (uint8_t *)&joystick,
    sizeof(joystick)
  );

  Serial.printf(
    "LY:%u LX:%u | U:%u D:%u L:%u R:%u | %s\n",
    joystick.ly, joystick.lx,
    joystick.dpadUp, joystick.dpadDown,
    joystick.dpadLeft, joystick.dpadRight,
    result == ESP_OK ? "Terkirim" : "Gagal"
  );

  delay(50);
}