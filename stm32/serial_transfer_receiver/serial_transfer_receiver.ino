#include <I2CTransfer.h>
#include <Packet.h>
#include <PacketCRC.h>
#include <SPITransfer.h>
#include <SerialTransfer.h>

void setup() {
Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String readInput = Serial.readStringUntil('\n');
    if (readInput == "Hi, aku STM32"){
      Serial.write("diterima!");
    }else{
      Serial.println("Menunggu Pesan...");
    }
  }else{
    Serial.println("Device not available.");
  }
  delay(1000);
}