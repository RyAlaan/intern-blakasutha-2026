#include <WiFi.h>
#include <esp_now.h>

// MAC Address ESP32 RX
uint8_t rxMAC[] = {
  0x68, 0xEE, 0x8F, 0x4F, 0x04, 0x1C
};

void setup() {
  // Memulai Serial Monitor
  Serial.begin(115200);

  // ESP32 sebagai Station
  WiFi.mode(WIFI_STA);

  // Memulai ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Error");
    return;
  }

  // Informasi perangkat RX
  esp_now_peer_info_t peerInfo = {};

  // Memasukkan MAC RX
  memcpy(peerInfo.peer_addr, rxMAC, 6);

  // Tidak menggunakan enkripsi
  peerInfo.encrypt = false;

  // Menambahkan RX
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Gagal menambahkan RX");
    return;
  }

  Serial.println("TX siap!");
  Serial.println("Ketik w/a/s/d lalu tekan Enter:");
}

void loop() {

  // Mengecek apakah ada data dari Serial Monitor
  if (Serial.available() > 0) {

    // Membaca 1 karakter
    char command = Serial.read();

    // Hanya menerima perintah w, a, s, d
    if (command == 'w' ||
        command == 'a' ||
        command == 's' ||
        command == 'd') {

      // Mengirim karakter ke RX
      esp_err_t result = esp_now_send(
        rxMAC,
        (uint8_t *)&command,
        sizeof(command)
      );

      // Menampilkan hasil pengiriman
      if (result == ESP_OK) {
        Serial.print("TX kirim: ");
        Serial.println(command);
      } else {
        Serial.println("Gagal mengirim!");
      }
    }
  }
}