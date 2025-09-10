// Clap Switch Project
// Turns LED on/off with a clap sound

const int soundSensorPin = A0; // Sound sensor connected to Analog Pin A0
const int ledPin = 3;          // LED connected to Digital Pin 7

int sensorValue = 0;         // Variable to store the sound sensor reading
bool ledState = false;       // Variable to store the current state of the LED (false = OFF, true = ON)

void setup() {
  pinMode(ledPin, OUTPUT);         // Set the LED pin as an output
  pinMode(soundSensorPin, INPUT);  // Set the sound sensor pin as an input
  Serial.begin(9600);              // Initialize serial communication for debugging
}

void loop() {
  sensorValue = analogRead(soundSensorPin); // Read the analog value from the sound sensor

  // Print the sensor value to the Serial Monitor for calibration
  Serial.println(sensorValue);
  delay(500);

  // Check if a sound exceeding a threshold is detected
  // The threshold value (e.g., 500) may need adjustment based on your sensor and environment
  if (sensorValue > 500) {
    ledState = !ledState;        // Toggle the LED state (ON to OFF, or OFF to ON)
    digitalWrite(ledPin, ledState); // Write the new state to the LED pin
    delay(500);                  // Debounce delay to prevent multiple triggers from a single clap
  }
}