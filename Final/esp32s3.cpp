#include <esp_now.h>
#include <WiFi.h>
#include <SerialTransfer.h>

SerialTransfer myTransfer;


struct STRUCT {
  int LY, LX, rX, rY;
  bool arUp, arDw, arRt, arLt;
} receivedData;

void onReceive(const uint8_t *mac, const uint8_t *incomingData, int len) {

  memcpy(&receivedData, incomingData, sizeof(STRUCT));

  Serial.printf("LX:%d LY:%d rX:%d rY:%d arUP:%d arDW:%d arRT:%d arLT:%d\n",
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
  Serial1.begin(115200, SERIAL_8N1, 44, 43); 
  myTransfer.begin(Serial1);

  WiFi.mode(WIFI_STA);
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());

  esp_now_init();
  esp_now_register_recv_cb(onReceive);
  
}

void loop() {
  uint16_t sendSize = 0;
  sendSize = myTransfer.txObj(receivedData, sendSize);
  myTransfer.sendData(sendSize);
  delay(50);
}
