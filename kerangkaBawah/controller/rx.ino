#include <esp_now.h>
#include <WiFi.h>

struct struct_message {
  int Lx, Ly, Rx, Ry;
  bool Up, Down, Right, Left; 
} controllerData;

void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t *incomingData, int len) {
  memcpy(&controllerData, incomingData, sizeof(controllerData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Lx: ");
  Serial.println(controllerData.Lx);
  Serial.print("Ly: ");
  Serial.println(controllerData.Ly);
  Serial.print("Rx: ");
  Serial.println(controllerData.Rx);
  Serial.print("Ry: ");
  Serial.println(controllerData.Ry);
  Serial.print("Up: ");
  Serial.println(controllerData.Up);
  Serial.print("Right: ");
  Serial.println(controllerData.Down);
  Serial.print("Left: ");
  Serial.println(controllerData.Right);
  Serial.print("Down: ");
  Serial.println(controllerData.Left);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  if(esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_init();
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  delay(1000);
}