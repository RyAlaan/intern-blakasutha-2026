#include <esp_now.h>
#include <WiFi.h>

struct struct_message {
  float Lx;
  float Ly;
  float Rx;
  float Ry;
  bool Up;
  bool Right;
  bool Left;
  bool Down; 
} Joystick;

void OnDataRecv(const esp_now_recv_info_t *esp_now_info, const uint8_t *incomingData, int len) {
  memcpy(&Joystick, incomingData, sizeof(Joystick));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Lx: ");
  Serial.println(Joystick.Lx);
  Serial.print("Ly: ");
  Serial.println(Joystick.Ly);
  Serial.print("Rx: ");
  Serial.println(Joystick.Rx);
  Serial.print("Ry: ");
  Serial.println(Joystick.Ry);
  Serial.print("Up: ");
  Serial.println(Joystick.Up);
  Serial.print("Right: ");
  Serial.println(Joystick.Right);
  Serial.print("Left: ");
  Serial.println(Joystick.Left);
  Serial.print("Down: ");
  Serial.println(Joystick.Down);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if(esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  delay(1600);
}