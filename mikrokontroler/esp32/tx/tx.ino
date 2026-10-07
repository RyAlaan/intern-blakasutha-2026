#include <WiFi.h>
#include <esp_now.h>

// MAC Address ESP32 RX
uint8_t rxMAC[] = {
  0x68, 0xEE, 0x8F, 0x4F, 0x04, 0x1C
};

void setup() {
  // Memulai Serial Monitor
  Serial.begin(115200);

  // Menggunakan mode Station
  WiFi.mode(WIFI_STA);

  // Memulai ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Error");
    return;
  }

  // Membuat informasi perangkat tujuan
  esp_now_peer_info_t peerInfo = {};

  // Memasukkan MAC Address RX
  memcpy(peerInfo.peer_addr, rxMAC, 6);

  // Tidak menggunakan enkripsi
  peerInfo.encrypt = false;

  // Menambahkan RX sebagai tujuan
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Gagal menambahkan RX");
    return;
  }

  Serial.println("TX siap!");
}

void loop() {
  // Data yang dikirim
  const char *msg = "Hello World";

  // Mengirim data ke RX
  esp_err_t result = esp_now_send(
    rxMAC,
    (uint8_t *)msg,
    strlen(msg) + 1
  );

  // Mengecek apakah pengiriman berhasil
  if (result == ESP_OK) {
    Serial.println("TX: Hello World");
  } else {
    Serial.println("Gagal mengirim");
  }

  // Tunggu 1 detik
  delay(1000);
}