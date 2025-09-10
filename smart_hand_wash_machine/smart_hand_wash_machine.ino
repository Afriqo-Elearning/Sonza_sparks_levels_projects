// Pin definitions
#define led 4
#define relay 3
#define trigPin 5
#define echoPin 6

long duration;
int distance;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(led, LOW);
  digitalWrite(relay, LOW);

  Serial.begin(9600);
}

void loop() {
  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  // Measure echo pulse
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert to cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If hands are near (< 15cm), activate relay + LED
  if (distance > 0 && distance < 15) {
    digitalWrite(relay, HIGH);  // Water pump ON
    digitalWrite(led, HIGH);    // LED ON
  } else {
    digitalWrite(relay, LOW);   // Water pump OFF
    digitalWrite(led, LOW);     // LED OFF
  }

  delay(200);
}
