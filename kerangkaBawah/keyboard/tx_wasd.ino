#include <esp_now.h> 
#include <WiFi.h>    

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x68, 0xEE, 0x8F, 0x4F, 0x04, 0x1C};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32]; 
  int b;      
  float c;    
  bool d;     
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;
 
void setup() {
    // Init Serial Monitor
    Serial.begin(115200);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
  
    // Register peer
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
    // Set values to send
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n'); 
        input.trim(); 
        
        if (input.length() > 0) {
            input.toCharArray(myData.a, sizeof(myData.a));

            esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
}}}