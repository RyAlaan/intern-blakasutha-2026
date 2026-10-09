#include <esp_now.h>
#include <WiFi.h>

struct STRUCT {
  int LY, LX, rX, rY;
  bool arUp, arDw, arRt, arLt;
} receivedData;

void onReceive(const uint8_t *mac, const uint8_t *incomingData, int len) {

  memcpy(&receivedData, incomingData, sizeof(STRUCT));

  Serial.printf("LX:%d LY:%d rX:%d rY:%d arUP:%d arDW:%d arRT:%d arLT:%d",
    receivedData.LX,
    receivedData.LY,
    receivedData.rX,
    receivedData.rY,
    receivedData.arUp,
    receivedData.arDw,
    receivedData.arRt,
    receivedData.arLt
  );
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());

  esp_now_init();
  esp_now_register_recv_cb(onReceive);
}

void loop() {}
