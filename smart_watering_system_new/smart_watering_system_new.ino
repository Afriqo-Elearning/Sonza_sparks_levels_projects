#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C address (commonly 0x27 or 0x3F)
// Adjust if nothing shows up on LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 8


#define DHTTYPE DHT11 

// Pin setup
const int soilPin = A0;   // Soil moisture sensor
const int relayPin = 7;   // Relay control
const int redLED = 4;     // Red LED
const int greenLED = 5;   // Green LED
const int buzzer = 6;

DHT dht(DHTPIN, DHTTYPE);

// Threshold value (tune according to your sensor)
// Lower value = wetter soil
int threshold = 500;

void setup() {
  // Pin modes
  pinMode(relayPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Initialize LCD
  lcd.init();

  dht.begin();

  lcd.backlight();

  // Serial monitor for debugging
  Serial.begin(9600);

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print(" Heaven System ");
  lcd.setCursor(0, 1);
  lcd.print("  System Init.... ");
  delay(2000);
  lcd.clear();

  digitalWrite(relayPin, LOW);
}

void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  Serial.println("Humidty:" + String(h));
  Serial.println("Temperature:" + String(t));

  // Read soil moisture
  int soilValue = analogRead(soilPin);
  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(soilValue);
  lcd.print("   "); // Clear old digits

  // Check soil moisture
  if (soilValue > threshold) {
    // Soil is dry → turn on relay, red LED
    digitalWrite(relayPin, HIGH); // Relay ON
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Soil Dry: PumpOn");
  } else {
    // Soil is wet enough → turn off relay, green LED
    digitalWrite(relayPin, LOW); // Relay OFF
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Soil OK: PumpOff");
  }

  delay(1000); // Wait 1 sec before next reading
}
