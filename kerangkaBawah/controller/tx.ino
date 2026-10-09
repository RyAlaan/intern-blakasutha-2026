#include <PS2X_lib.h> 
#include <WiFi.h>
#include <esp_now.h>

#define PS2_DAT 19  
#define PS2_CMD 23  
#define PS2_SEL 5  
#define PS2_CLK 18  

#define pressures false
#define rumble false

PS2X ps2x;

int error = -1;
byte type = 0;
int tryNum = 1;

uint8_t broadcastAddress[] = {0x68, 0xEE, 0x8F, 0x4F, 0x04, 0x1C};
struct struct_message {
  int LX, LY, RX, RY;
  bool UP, DOWN, RIGHT, LEFT;
} controllerData;

esp_now_peer_info_t peerInfo; 

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup(){
  Serial.begin(115200);
  while (error != 0) {
    delay(1000);
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    Serial.print("#try config ");
    Serial.println(tryNum);
    tryNum ++;
  }

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
  if (error != 0) {
    Serial.println("PS not connected");
    delay(1000);
    return;
  }

  ps2x.read_gamepad(false, 0); 

  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) {
  controllerData.LX = ps2x.Analog(PSS_LX);
  controllerData.LY = ps2x.Analog(PSS_LY);
  controllerData.RX = ps2x.Analog(PSS_RX);
  controllerData.RY = ps2x.Analog(PSS_RY);
  controllerData.UP = ps2x.Button(PSB_PAD_UP);
  controllerData.DOWN = ps2x.Button(PSB_PAD_DOWN);
  controllerData.RIGHT = ps2x.Button(PSB_PAD_RIGHT);
  controllerData.LEFT = ps2x.Button(PSB_PAD_LEFT);

  if (memcmp(&controllerData, &lastControllerData, sizeof(controllerData)) != 0) {
    esp_now_send(broadcastAddress, (uint8_t *) &controllerData, sizeof(controllerData));
    memcpy(&lastControllerData, &controllerData, sizeof(controllerData));
  }

  delay(50);
}}