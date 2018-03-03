#include <SoftwareSerial.h>

SoftwareSerial BTSerial(11, 12); // RX | TX

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);  // your own BT Module default speed in AT command more
}

void loop() {
  // Keep reading from BT Module and send to Arduino Serial Monitor
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }

  // Keep reading from Arduino Serial Monitor and send to BT Module
  if (Serial.available()) {
    //Serial.println(Serial.read());
    BTSerial.write(Serial.read());
  }
}
