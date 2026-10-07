#include <WiFi.h>              // Library Wi-Fi ESP32
#include <esp_now.h>           // Library komunikasi ESP-NOW


void setup() {

  // Memulai Serial Monitor
  Serial.begin(115200);

  // Mengubah ESP32 menjadi mode Station
  // Diperlukan untuk menggunakan ESP-NOW
  WiFi.mode(WIFI_STA);

  // Menampilkan MAC Address ESP32 RX
  Serial.print("MAC RX: ");
  Serial.println(WiFi.macAddress());

  // Memulai ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Error"); // Jika gagal
    return;                           // Hentikan setup
  }

  // Membuat fungsi yang akan dijalankan
  // setiap kali ada data masuk
  esp_now_register_recv_cb(
    [](const esp_now_recv_info_t *info,
       const uint8_t *data,
       int len) {

      // Menampilkan tulisan "RX:"
      Serial.print("RX: ");

      // Mengubah data yang diterima menjadi teks
      // lalu menampilkannya di Serial Monitor
      Serial.println((char *)data);
    }
  );
}

void loop() {

  // Tidak perlu melakukan apa-apa di loop
  // Karena RX akan otomatis menerima data
  // melalui callback di atas

}