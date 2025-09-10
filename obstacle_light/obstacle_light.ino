#define TRIG_PIN 8
#define ECHO_PIN 9

int leds[] = {3, 4, 5, 6};
int buzzer = 7;

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(buzzer, OUTPUT);
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

  if (distance > 0 && distance <= 15) {
    // Turn ON LEDs + buzzer
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
    }
    digitalWrite(buzzer, HIGH);
  } else {
    // Turn OFF LEDs + buzzer
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);
    }
    digitalWrite(buzzer, LOW);
  }

  delay(200);
}
