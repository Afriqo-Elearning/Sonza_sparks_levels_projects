// Pin definitions
#define SOIL_SENSOR_PIN A0
#define RELAY_PIN 7
#define GREEN_LED 3
#define RED_LED 4

// Moisture thresholds (tweak for your sensor)
int dryThreshold = 500;   // Above this = dry soil
int wetThreshold = 400;   // Below this = very wet

void setup() {
  Serial.begin(9600);

  // Set pin modes
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Turn everything off initially
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void loop() {
  int soilValue = analogRead(SOIL_SENSOR_PIN);
  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  if (soilValue > dryThreshold) {
    // Soil is dry 🌵
    digitalWrite(RELAY_PIN, HIGH);     // Turn ON relay (water the plant)
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Serial.println("🌵 Soil is dry. Watering...");
  }
  else if (soilValue < wetThreshold) {
    // Soil is too wet 💦
    digitalWrite(RELAY_PIN, LOW);      // Turn OFF relay
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    Serial.println("💧 Soil is wet. No watering.");
  }
  else {
    // Soil is okay 🌱
    digitalWrite(RELAY_PIN, LOW);      // No need to water
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    Serial.println("🌱 Soil is good.");
  }

  delay(2000);  // Check every 2 seconds
}
