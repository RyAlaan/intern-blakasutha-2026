#include <esp_now.h>
#include <WiFi.h>
#include "SerialTransfer.h"

SerialTransfer myTransfer;

struct __attribute__((packed)) struct_message {
  float Lx;
  float Ly;
  float Rx;
  float Ry;
  bool Up;
  bool Right;
  bool Left;
  bool Down; 
} Joystick;

volatile unsigned long LastInput = 0;
unsigned long LastPrint = 0;

void OnDataRecv(const esp_now_recv_info_t *esp_now_info, const uint8_t *incomingData, int len) {
  if (len != sizeof(Joystick)) return;
  memcpy(&Joystick, incomingData, sizeof(Joystick));
  LastInput = millis();
  if((millis() - LastPrint) >= 200) {
    LastPrint = millis();
    // Serial.print("Bytes received: ");
    // Serial.println(len);
    Serial.print(Joystick.Lx);
    Serial.print(" | ");
    Serial.print(Joystick.Ly);
    Serial.print(" | ");
    Serial.print(Joystick.Rx);
    Serial.print(" | ");
    Serial.println(Joystick.Ry);
    // Serial.print("Up: ");
    // Serial.println(Joystick.Up);
    // Serial.print("Right: ");
    // Serial.println(Joystick.Right);
    // Serial.print("Left: ");
    // Serial.println(Joystick.Left);
    // Serial.print("Down: ");
    // Serial.println(Joystick.Down);
  }
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 18, 17);
  myTransfer.begin(Serial1);
  WiFi.mode(WIFI_STA);
  if(esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  uint16_t sendSize = 0;
  if((millis() - LastInput) > 400) memset(&Joystick, 0, sizeof(Joystick));
  sendSize = myTransfer.txObj(Joystick, sendSize);
  myTransfer.sendData(sendSize);
  delay(50);
}