#include <esp_now.h> 
#include <WiFi.h>   

typedef struct struct_message {
  char a[32]; 
  int b;     
  float c;    
  bool d;     
} struct_message;

struct_message myData;

void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
    
  char tombol = myData.a[0];

  if (tombol == 'w') {
    Serial.println("Maju");
  } else if (tombol == 's') {
    Serial.println("Mundur");
  } else if (tombol == 'a') {
    Serial.println("Kiri");
  } else if (tombol == 'd') {
    Serial.println("Kanan");
  } 
}
 
void setup() {
  Serial.begin(115200);
   
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) { 
    Serial.println("Error initializing ESP-NOW"); 
    return; 
  }

  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  
}