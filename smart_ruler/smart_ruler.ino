#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ----- LCD Setup (Optional) -----
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change to 0x3F if blank

// ----- Pin Definitions -----
const int trigPin = A0;  // Can also use D7
const int echoPin = A1;  // Can also use D8

// ----- Variables -----
long duration;
float distance;

void setup() {
  Serial.begin(9600);

  // Pin setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ultrasonic Sensor");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  // ----- Trigger the sensor -----
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // ----- Read Echo -----
  duration = pulseIn(echoPin, HIGH);

  // ----- Calculate distance in cm -----
  distance = (duration * 0.0343) / 2;

  // ----- Print to Serial Monitor -----
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ----- Display on LCD (if connected) -----
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm  ");

  delay(500); // Update twice per second
}