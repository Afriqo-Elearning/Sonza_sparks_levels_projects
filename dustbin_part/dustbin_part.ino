// Ultrasonic Sensor Pins
#define TRIG_PIN A0
#define ECHO_PIN A1

// Relay pin
const int RELAY_PIN = 7;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // relay OFF initially
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If hand detected within 15 cm → turn ON relay
  if (distance > 0 && distance <= 15) {
    digitalWrite(RELAY_PIN, LOW);  // relay ON
  } else {
    digitalWrite(RELAY_PIN, HIGH);   // relay OFF
  }

  delay(100);
}
