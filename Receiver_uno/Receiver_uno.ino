#include <VirtualWire.h>

void setup() {
  Serial.begin(9600);
  vw_set_tx_pin(12);      // TX pin
  vw_setup(2000);         // Bits per second
  Serial.println("Ready to send...");
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();  // Read single char like '1', '2', etc.

    if (input >= '0' && input <= '4') {
      char msg[2] = {input, '\0'};
      vw_send((uint8_t*)msg, strlen(msg));
      vw_wait_tx(); // Wait for message to send
      Serial.print("Sent: "); Serial.println(msg);
    }
  }
}
