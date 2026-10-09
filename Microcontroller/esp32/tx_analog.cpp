#include <PS2X_lib.h>
#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverMAC[] = {0x68, 0xEE, 0x8F, 0x4F, 0x04, 0x1C};

struct STRUCT {
  int LY, LX, rX, rY;
  bool arUp, arDw, arRt, arLt;
} data;

esp_now_peer_info_t peer;
PS2X ps2x;
int error = -1;
byte type = 0;

void onSent(const uint8_t *mac, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Terkirim" : "Gagal");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Gagal init ESP-NOW");
    return;
  }
  esp_now_register_send_cb(onSent);

  memcpy(peer.peer_addr, receiverMAC, 6);
  peer.channel = 0;
  peer.encrypt = false;
  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("Gagal tambah peer");
    return;
  }

  Serial.println("ESP-NOW OK, init PS2...");

  int tryNum = 0;
  while (error != 0 && tryNum < 5) {
    delay(500);
    error = ps2x.config_gamepad(18, 23, 5, 19, false, false);
    Serial.printf("PS2 try %d: error=%d\n", ++tryNum, error);
  }

  if (error != 0) {
    Serial.println("PS2 gagal konek, cek wiring!");
  } else {
    type = ps2x.readType();
    Serial.printf("PS2 type: %d\n", type);
  }
}

void loop() {
  if (error != 0) {
    Serial.println("PS2 tidak terhubung");
    delay(2000);
    return;
  }

  ps2x.read_gamepad(false, 0);

  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) {
  data.LX = ps2x.Analog(PSS_LX);
  data.LY = ps2x.Analog(PSS_LY);
  data.rX = ps2x.Analog(PSS_RX);
  data.rY = ps2x.Analog(PSS_RY);
  data.arUp = ps2x.Button(PSB_PAD_UP);
  data.arDw = ps2x.Button(PSB_PAD_DOWN);
  data.arRt = ps2x.Button(PSB_PAD_RIGHT);
  data.arLt = ps2x.Button(PSB_PAD_LEFT);
  Serial.println(data.rX);
  Serial.println(data.arUp);
  esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));
  }
  delay(50);
}




