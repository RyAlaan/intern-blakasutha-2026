#include <esp_now.h>
#include <WiFi.h>
#include <SerialTransfer.h>

SerialTransfer myTransfer;

#define TX2_PIN 17
#define RX2_PIN 16

struct __attribute__((packed)) struct_message {
  int LX, LY, RX, RY;
  bool UP, DOWN, RIGHT, LEFT; 
} controllerData;

void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t *incomingData, int len) {
  memcpy(&controllerData, incomingData, sizeof(controllerData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("LX: ");
  Serial.println(controllerData.LX);
  Serial.print("LY: ");
  Serial.println(controllerData.LY);
  Serial.print("RX: ");
  Serial.println(controllerData.RX);
  Serial.print("RY: ");
  Serial.println(controllerData.RY);
  Serial.print("UP: ");
  Serial.println(controllerData.UP);
  Serial.print("DOWN: ");
  Serial.println(controllerData.DOWN);
  Serial.print("RIGHT: ");
  Serial.println(controllerData.RIGHT);
  Serial.print("LEFT: ");
  Serial.println(controllerData.LEFT);

  uint16_t sendSize = 0;
  sendSize = myTransfer.txObj(controllerData, sendSize);
  myTransfer.sendData(sendSize);
}

void setup() {
  Serial.begin(115200);

  Serial2.begin(115200, SERIAL_8N1, RX2_PIN, TX2_PIN);
  myTransfer.begin(Serial2);

  WiFi.mode(WIFI_STA);

  Serial.print("MAC Receiver: ");
  Serial.println(WiFi.macAddress());

  if(esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
  Serial.println("ESP32-S3 Ready!");
}

void loop() {
  delay(1000);
}