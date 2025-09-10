#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// Pins for outputs
#define ROOM_BULB_PIN     17
#define SITTING_BULB_PIN  16
#define BEDROOM_BULB_PIN  19
#define FAN_PIN           18
#define STATUS_LED_PIN    13   // Built-in LED on most ESP32s

unsigned long lastBlinkTime = 0;
bool ledState = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Device");

  
  pinMode(ROOM_BULB_PIN, OUTPUT);
  pinMode(SITTING_BULB_PIN, OUTPUT);
  pinMode(BEDROOM_BULB_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);

  Serial.println("Bluetooth device is ready to pair.");
}






void loop() {
  // LED Status blinking if NOT connected
  if (!SerialBT.hasClient()) {
    if (millis() - lastBlinkTime >= 500) {
      ledState = !ledState;
      digitalWrite(STATUS_LED_PIN, ledState);
      lastBlinkTime = millis();
    }
  } else {
    digitalWrite(STATUS_LED_PIN, HIGH); // Solid ON if connected
  }

  // Check for Bluetooth commands
  if (SerialBT.available()) {
    char cmd = SerialBT.read();

    switch (cmd) {
      case '1':
        digitalWrite(ROOM_BULB_PIN, HIGH);
        SerialBT.println("Room Bulb ON");
        break;
      case '2':
        digitalWrite(ROOM_BULB_PIN, LOW);
        SerialBT.println("Room Bulb OFF");
        break;
      case '3':
        digitalWrite(SITTING_BULB_PIN, HIGH);
        SerialBT.println("Sitting Bulb ON");
        break;
      case '4':
        digitalWrite(SITTING_BULB_PIN, LOW);
        SerialBT.println("Sitting Bulb OFF");
        break;
      case '5':
        digitalWrite(BEDROOM_BULB_PIN, HIGH);
        SerialBT.println("Bedroom Bulb ON");
        break;
      case '6':
        digitalWrite(BEDROOM_BULB_PIN, LOW);
        SerialBT.println("Bedroom Bulb OFF");
        break;
      case '7':
        digitalWrite(FAN_PIN, HIGH);
        SerialBT.println("Fan ON");
        break;
      case '8':
        digitalWrite(FAN_PIN, LOW);
        SerialBT.println("Fan OFF");
        break;
      default:
        SerialBT.println("Unknown command");
        break;
    }
  }
}
