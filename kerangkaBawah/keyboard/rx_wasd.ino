#include <esp_now.h> 
#include <WiFi.h>   

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32]; 
    int b;     
    float c;    
    bool d;     
} struct_message;

// Create a struct_message called myData
struct_message myData;

void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));
    
    char tombol = myData.a[0];

    if (tombol == 'w' || tombol == 'W') {
        Serial.println("Aksi: MAJU");
    } 
    else if (tombol == 's' || tombol == 'S') {
        Serial.println("Aksi: MUNDUR");
    } 
    else if (tombol == 'a' || tombol == 'A') {
        Serial.println("Aksi: KIRI");
    } 
    else if (tombol == 'd' || tombol == 'D') {
        Serial.println("Aksi: KANAN");
    } 
}
 
void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);
    
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) { 
        Serial.println("Error initializing ESP-NOW"); 
        return; 
  }
  
    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  
}