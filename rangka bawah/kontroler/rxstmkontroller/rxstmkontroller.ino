#include "SerialTransfer.h"

SerialTransfer myTransfer;

struct __attribute__((packed)) JoystickPacket {
  uint8_t ly;
  uint8_t lx;
  uint8_t ry;
  uint8_t rx;

  uint8_t dpadUp;
  uint8_t dpadDown;
  uint8_t dpadLeft;
  uint8_t dpadRight;
} joystick;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  myTransfer.begin(Serial1);

  Serial.println("STM32 siap!");
}

void loop() {
  if (myTransfer.available()) {
    uint16_t recSize = 0;

    recSize = myTransfer.rxObj(joystick, recSize);

    if (joystick.dpadUp) {
      Serial.println("MAJU");
    }
    else if (joystick.dpadDown) {
      Serial.println("MUNDUR");
    }
    else if (joystick.dpadRight) {
      Serial.println("KANAN");
    }
    else if (joystick.dpadLeft) {
      Serial.println("KIRI");
    }
    else {
      Serial.println("BERHENTI");
    }
  }
}