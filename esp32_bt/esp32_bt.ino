#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// UART pins to Arduino
#define RXD2 26  // Connect to Arduino TX (Pin 3)
#define TXD2 27  // Connect to Arduino RX (Pin 2)

void setup() {
  Serial.begin(115200);  // For debug
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // UART to Arduino
  SerialBT.begin("ESP32_BT");  // Name it like HC-06
  Serial.println("Bluetooth started, waiting for connection...");
}

void loop() {
  // If phone sends data via BT, send to Arduino
  if (SerialBT.available()) {
    char data = SerialBT.read();
    Serial2.write(data);     // Send to Arduino
    Serial.print("From phone: ");
    Serial.println(data);
  }

  // Optional: if Arduino sends data back, relay to phone
  if (Serial2.available()) {
    char dataFromArduino = Serial2.read();
    SerialBT.write(dataFromArduino);
    Serial.print("From Arduino: ");
    Serial.println(dataFromArduino);
  }

  delay(10);
}
