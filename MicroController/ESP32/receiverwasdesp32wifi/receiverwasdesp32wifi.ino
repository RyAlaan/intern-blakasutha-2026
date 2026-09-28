#include <esp_now.h>
#include <WiFi.h>
#include <bits/stdc++.h>

struct struct_message {
  char move;
} TesData;

String TheMove(char move) {
  if(move == 'w') return "maju";
  else if(move == 'a') return "kiri";
  else if(move == 'd') return "kanan";
  else if(move == 's') return "mundur";
  else return "";
}

void OnDataRecv(const esp_now_recv_info_t *esp_now_info, const uint8_t *incomingData, int len) {
  memcpy(&TesData, incomingData, sizeof(TesData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.println(TheMove(TesData.move));
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
