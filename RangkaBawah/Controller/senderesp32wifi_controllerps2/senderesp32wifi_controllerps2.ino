#include <PS2X_lib.h>  //for v1.6
#include <WiFi.h>
#include <esp_now.h>

#define PS2_DAT        19  //MISO  19
#define PS2_CMD        23  //MOSI  23
#define PS2_SEL         5  //SS     5
#define PS2_CLK        18  //SLK   18

#define pressures   false
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

int error = -1;
byte type = 0;
byte vibrate = 0;
int tryNum = 1;

uint8_t broadcastAddress[] = {0x68, 0xEE, 0x8F, 0x4F, 0x04, 0x1C};
struct struct_message {
  float Lx;
  float Ly;
  float Rx;
  float Ry;
  bool Up;
  bool Right;
  bool Left;
  bool Down;
} Joystick;

esp_now_peer_info_t peerInfo; 

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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
  Serial.println(ps2x.Analog(1), HEX);
  type = ps2x.readType();
  switch(type) {
    case 0:
      Serial.println(" Unknown Controller type found ");
      break;
    case 1:
      Serial.println(" DualShock Controller found ");
      break;
    case 2:
      Serial.println(" GuitarHero Controller found ");
      break;
	  case 3:
      Serial.println(" Wireless Sony DualShock Controller found ");
      break;
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
  Joystick.Up = ps2x.Button(PSB_PAD_UP);
  Joystick.Right = ps2x.Button(PSB_PAD_RIGHT);
  Joystick.Left = ps2x.Button(PSB_PAD_LEFT);
  Joystick.Down = ps2x.Button(PSB_PAD_DOWN);

  ps2x.read_gamepad(false, 0); 
  Serial.print("Stick Values:");
  Serial.print(ps2x.Analog(PSS_LX));
  Joystick.Lx = ps2x.Analog(PSS_LX);
  Serial.print(",");
  Serial.print(ps2x.Analog(PSS_LY), DEC);
  Joystick.Ly = ps2x.Analog(PSS_LY);
  Serial.print(",");
  Serial.println(ps2x.Analog(PSS_RX), DEC);
  Joystick.Rx = ps2x.Analog(PSS_RX);
  Serial.print(","); 
  Serial.print(ps2x.Analog(PSS_RY), DEC);
  Joystick.Ry = ps2x.Analog(PSS_RY);
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &Joystick, sizeof(Joystick));
  /*if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }*/
  delay(50);
}