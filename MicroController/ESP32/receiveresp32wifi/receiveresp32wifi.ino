#include <esp_now.h>
#include <WiFi.h>

struct struct_message {
  char z;
  float y;  
} TesData;

void OnDataRecv(const esp_now_recv_info_t *esp_now_info, const uint8_t *incomingData, int len) {
  memcpy(&TesData, incomingData, sizeof(TesData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(TesData.z);
  Serial.print("Float: ");
  Serial.println(TesData.y);
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
