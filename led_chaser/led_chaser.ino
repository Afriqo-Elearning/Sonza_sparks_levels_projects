const int ledPins[] = {
  2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23
};
const int NUM_LEDS = sizeof(ledPins) / sizeof(ledPins[0]);

const int MODE_PIN = 33; // Button to change mode (connect to GND with pullup)
int mode = 0;
unsigned long lastDebounce = 0;
bool lastBtnState = HIGH;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(MODE_PIN, INPUT_PULLUP);
  Serial.println("LED Chaser Ready");
}

void loop() {
  checkButton();

  switch (mode) {
    case 0: modeLeftToRight(); break;
    case 1: modeRightToLeft(); break;
    case 2: modePingPong(); break;
    case 3: modeEvenOdd(); break;
    case 4: modeCenterOut(); break;
    case 5: modeAllBlink(); break;
  }
}

// -------------- MODES -----------------

void modeLeftToRight() {
  for (int i = 0; i < NUM_LEDS; i++) {
    setOneLed(i);
    delay(100);
  }
}

void modeRightToLeft() {
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    setOneLed(i);
    delay(100);
  }
}

void modePingPong() {
  for (int i = 0; i < NUM_LEDS; i++) {
    setOneLed(i);
    delay(80);
  }
  for (int i = NUM_LEDS - 2; i > 0; i--) {
    setOneLed(i);
    delay(80);
  }
}

void modeEvenOdd() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], (i % 2 == 0) ? HIGH : LOW);
  }
  delay(300);
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], (i % 2 != 0) ? HIGH : LOW);
  }
  delay(300);
}

void modeCenterOut() {
  int center = NUM_LEDS / 2;
  for (int offset = 0; offset <= center; offset++) {
    int left = center - offset;
    int right = center + offset;
    if (left >= 0) digitalWrite(ledPins[left], HIGH);
    if (right < NUM_LEDS) digitalWrite(ledPins[right], HIGH);
    delay(150);
    if (left >= 0) digitalWrite(ledPins[left], LOW);
    if (right < NUM_LEDS) digitalWrite(ledPins[right], LOW);
  }
}

void modeAllBlink() {
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(ledPins[i], HIGH);
  delay(300);
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(ledPins[i], LOW);
  delay(300);
}

// ----------- UTILITY FUNCTIONS ----------

void setOneLed(int index) {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], (i == index) ? HIGH : LOW);
  }
}

void checkButton() {
  bool btn = digitalRead(MODE_PIN);
  if (btn == LOW && lastBtnState == HIGH && millis() - lastDebounce > 200) {
    mode = (mode + 1) % 6;
    Serial.print("Switched to Mode: ");
    Serial.println(mode);
    lastDebounce = millis();
  }
  lastBtnState = btn;
}
