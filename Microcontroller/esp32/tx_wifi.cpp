#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverMAC[] = {0x1C, 0xDB, 0xD4, 0xD2, 0xC0, 0x94};

struct STRUCT {
    char cmd;
} tesData;

esp_now_peer_info_t peer;

void onSent(const uint8_t *mac, esp_now_send_status_t status) {
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Terkirim" : "Gagal");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Gagal menginisialisasi ESP-NOW");
        return;
    }
    
    esp_now_register_send_cb(onSent);

    memcpy(peer.peer_addr, receiverMAC, 6);
    peer.channel = 0;
    peer.encrypt = false;
    
    if (esp_now_add_peer(&peer) != ESP_OK) {
        Serial.println("Gagal menambahkan peer");
        return;
    }
}

void loop() {
    if (Serial.available() > 0) {
        String msg = Serial.readString();
    
        
        if (msg.length() > 0) {
            tesData.cmd = msg[0];
            
            esp_now_send(receiverMAC, (uint8_t *)&tesData, sizeof(tesData));
        }
    }
}

 
