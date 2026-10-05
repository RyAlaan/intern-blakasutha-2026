#include <esp_now.h> 
#include <WiFi.h>    

uint8_t broadcastAddress[] = {};

typedef struct struct_message {
  char a[32]; 
  int b;      
  float c;    
  bool d;     
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;
 
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
 
  memcpy(peerInfo.peer_addr, broadcastAddress, 6); 
  peerInfo.channel = 0;                            
  peerInfo.encrypt = false;                        

  if (esp_now_add_peer(&peerInfo) != ESP_OK){ 
    Serial.println("Gagal menambahkan peer");     
    return;                                   
  }

  Serial.println("Ketik w, a, s, d lalu Enter.");
}
 
void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 
       
    if (input.length() > 0) {
      input.toCharArray(myData.a, sizeof(myData.a));

      esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    }
  }
}