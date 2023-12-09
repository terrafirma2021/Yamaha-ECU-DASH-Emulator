#include <Arduino.h>

HardwareSerial &DASH = Serial1;
HardwareSerial &ECU = Serial2;

const unsigned long DASH_DELAY = 1288;
const unsigned long POLL_DELAY = 16;
const unsigned long FE_TIMEOUT = 15.7;  // Timeout for 0xFE in milliseconds
const unsigned long ONE_TIMEOUT = 2876; // Timeout for 0x01 in microseconds

void setup() {
  Serial.begin(115200); // Initialize Serial Monitor
  DASH.begin(16040);    // DASH UART
  ECU.begin(16040);     // ECU UART

  // Flush the serial buffers
  DASH.flush();
  ECU.flush();
}

void ecuRespond() {
  delayMicroseconds(2876); // ECU delay before responding
  ECU.write(0x00);
  ECU.write(0x00);
  ECU.write(0x00);
  ECU.write(0x01);
  ECU.write(0x01);
  Serial.println("ECU TX: 0x00 0x00 0x00 0x01 0x01");
}

void loop() {
  delay(DASH_DELAY);

  DASH.write(0xFE);
  Serial.println("DASH TX: 0xFE");
  delay(POLL_DELAY);

  unsigned long startTime = millis();
  bool feResponseReceived = false;

  while (millis() - startTime < FE_TIMEOUT) {
    if (DASH.available() >= 5) {
      byte response[5];
      DASH.readBytes(response, 5);
      if (response[0] == 0x00 && response[1] == 0x00 && response[2] == 0x00 && response[3] == 0x01 && response[4] == 0x01) {
        feResponseReceived = true;
        break;
      }
    }
    if (ECU.available() > 0 && ECU.read() == 0xFE) {
      ecuRespond();
    }
  }

  if (!feResponseReceived) {
    Serial.println("DASH: ER-1 0xFE");
    return;
  }

  while (true) {
    DASH.write(0x01);
    Serial.println("DASH TX: 0x01");
    delay(POLL_DELAY);

    startTime = millis();
    bool oneResponseReceived = false;

    while (millis() - startTime < ONE_TIMEOUT) {
      if (DASH.available() >= 5) {
        byte response[5];
        DASH.readBytes(response, 5);
        if (response[0] == 0x00 && response[1] == 0x00 && response[2] == 0x00 && response[3] == 0x01 && response[4] == 0x01) {
          oneResponseReceived = true;
          break;
        }
      }
      if (ECU.available() > 0 && ECU.read() == 0x01) {
        ecuRespond();
      }
    }

    if (!oneResponseReceived) {
      Serial.println("DASH: ER-2 0x01");
      continue;
    }
  }
}
