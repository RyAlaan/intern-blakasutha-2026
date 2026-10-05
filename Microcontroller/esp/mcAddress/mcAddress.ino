#include <esp_now.h>
#include <WiFi.h>

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
}

void loop()
{
  Serial.println(WiFi.macAddress());
  delay(100);
}

//68:EE:8F:4F:04:1C