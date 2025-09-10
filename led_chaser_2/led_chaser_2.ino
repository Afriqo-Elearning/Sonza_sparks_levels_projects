const int ledPins[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
  12, 13, 14, 15, 16, 17, 18, 19,
  20, 21, 22, 23
};
const int NUM_LEDS = sizeof(ledPins) / sizeof(ledPins[0]);

int mode = 0;
unsigned long lastModeSwitch = 0;
const unsigned long MODE_DURATION = 5000; // 5 seconds per mode

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  randomSeed(analogRead(0)); // seed randomness
  Serial.println("Auto LED Chaser Started");
}

void loop() {
  if (millis() - lastModeSwitch > MODE_DURATION) {
    mode = (mode + 1) % 9;  // now 9 total modes!
    lastModeSwitch = millis();
    Serial.print("Switching to Mode: ");
    Serial.println(mode);
  }

  switch (mode) {
    case 0: modeLeftToRight(); break;
    case 1: modeRightToLeft(); break;
    case 2: modePingPong(); break;
    case 3: modeEvenOdd(); break;
    case 4: modeCenterOut(); break;
    case 5: modeAllBlink(); break;
    case 6: modeRandomTwinkleSlow(); break;
    case 7: modeFireBurst(); break;
    case 8: modeWaveRoll(); break;
  }
}

// -------------- MODES -----------------

void modeLeftToRight() {
  for (int i = 0; i < NUM_LEDS; i++) {
    setOneLed(i);
    delay(80);
  }
}

void modeRightToLeft() {
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    setOneLed(i);
    delay(80);
  }
}

void modePingPong() {
  for (int i = 0; i < NUM_LEDS; i++) {
    setOneLed(i);
    delay(60);
  }
  for (int i = NUM_LEDS - 2; i > 0; i--) {
    setOneLed(i);
    delay(60);
  }
}

void modeEvenOdd() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], (i % 2 == 0) ? HIGH : LOW);
  }
  delay(250);
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], (i % 2 != 0) ? HIGH : LOW);
  }
  delay(250);
}

void modeCenterOut() {
  int center = NUM_LEDS / 2;
  for (int offset = 0; offset <= center; offset++) {
    int left = center - offset;
    int right = center + offset;
    if (left >= 0) digitalWrite(ledPins[left], HIGH);
    if (right < NUM_LEDS) digitalWrite(ledPins[right], HIGH);
    delay(120);
    if (left >= 0) digitalWrite(ledPins[left], LOW);
    if (right < NUM_LEDS) digitalWrite(ledPins[right], LOW);
  }
}

void modeAllBlink() {
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(ledPins[i], HIGH);
  delay(400);
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(ledPins[i], LOW);
  delay(400);
}

void modeRandomTwinkleSlow() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], random(0, 2));
  }
  delay(300);  // slower random twinkle
}

void modeFireBurst() {
  int center = NUM_LEDS / 2;
  int blastSteps = random(3, center);

  // Fire rising
  for (int i = center; i >= center - blastSteps; i--) {
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[NUM_LEDS - 1 - i], HIGH);
    delay(70);
  }

  // Hold a sec
  delay(150);

  // Big blast out!
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(100);
}

void modeWaveRoll() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(50);
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(50);
    digitalWrite(ledPins[i], LOW);
  }
}

// ---------- Utility ------------------

void setOneLed(int index) {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], (i == index) ? HIGH : LOW);
  }
}
