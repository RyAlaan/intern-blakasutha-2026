#include <WiFi.h>
#include <esp_now.h>
#include <bits/stdc++.h>

uint8_t broadcastAddress[] = {0x98, 0x88, 0xE0, 0x03, 0xF8, 0xAC};
struct struct_message {
  char move;
} TesData;
String input;

esp_now_peer_info_t peerInfo; 

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if(esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb((esp_now_send_cb_t) OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if(esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;   
  }
}

void loop() {
  if(Serial.available() > 0) {
    input = Serial.readStringUntil('\n');
    TesData.move = input[0];
  }
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &TesData, sizeof(TesData));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  delay(1600);
}
