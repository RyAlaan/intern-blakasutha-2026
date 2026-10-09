#include <WiFi.h>
#include <esp_now.h>

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

const int DEADZONE_LOW = 100;
const int DEADZONE_HIGH = 155;

void onDataRecv(const esp_now_recv_info_t *info,
                const uint8_t *data, int len) {
  if (len != sizeof(JoystickPacket)) {
    return;
  }

  memcpy(&joystick, data, sizeof(joystick));

  if (joystick.dpadUp) {
    Serial.println("MAJU");
  }
  else if (joystick.dpadDown) {
    Serial.println("MUNDUR");
  }
  else if (joystick.dpadLeft) {
    Serial.println("KIRI");
  }
  else if (joystick.dpadRight) {
    Serial.println("KANAN");
  }
  else if (joystick.ly < DEADZONE_LOW) {
    Serial.println("MAJU");
  }
  else if (joystick.ly > DEADZONE_HIGH) {
    Serial.println("MUNDUR");
  }
  else if (joystick.lx < DEADZONE_LOW) {
    Serial.println("KIRI");
  }
  else if (joystick.lx > DEADZONE_HIGH) {
    Serial.println("KANAN");
  }
  else {
    Serial.println("STOP");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Error");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
  Serial.println("RX siap!");
}

void loop() {
}
