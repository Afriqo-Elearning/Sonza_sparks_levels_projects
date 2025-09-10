#define pir 7
int leds[] = {3, 4, 5, 6};

unsigned long lastMotionTime = 0;
const unsigned long ledOnTime = 1000; // keep LED ON for 1s after motion

void setup() {
  Serial.begin(9600);
  pinMode(pir, INPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  int motion = digitalRead(pir);

  if (motion == HIGH) {
    lastMotionTime = millis(); // reset timer when motion detected
  }

  // if within ledOnTime of last motion, keep LEDs ON
  if (millis() - lastMotionTime < ledOnTime) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
    }
  } else {
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);
    }
  }

  Serial.println(motion);
}
