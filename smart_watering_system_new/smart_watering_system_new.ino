#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 8
#define DHTTYPE DHT11

// Pin setup
const int soilPin   = A0;   // Soil moisture sensor
const int relayPin  = 7;    // Relay control (pump)
const int redLED    = 4;    // Red LED = warning
const int greenLED  = 5;    // Green LED = OK
const int buzzer    = 6;

DHT dht(DHTPIN, DHTTYPE);

// Chinese Spinach thresholds
const int soilMin = 250;     // Moist soil limit
const int soilMax = 350;     // Above this = too dry

const int tempMin = 25;      // Minimum temperature
const int tempMax = 35;      // Maximum temperature

const int humMin  = 55;      // Min humidity %
const int humMax  = 65;      // Max humidity %

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();
  dht.begin();
  Serial.begin(9600);

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print(" Heaven System ");
  lcd.setCursor(0, 1);
  lcd.print("  Init Crop Mode ");
  delay(2000);
  lcd.clear();

  digitalWrite(relayPin, LOW);
}

void loop() {
  // Read sensors
  int soilValue = analogRead(soilPin);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Debug print
  Serial.print("Soil: "); Serial.print(soilValue);
  Serial.print(" | Temp: "); Serial.print(t);
  Serial.print("C | Humidity: "); Serial.print(h);
  Serial.println("%");

  // LCD line 0 = sensor values
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(soilValue);
  lcd.print(" T:");
  lcd.print(t, 0);
  lcd.print(" H:");
  lcd.print(h, 0);

  // ----- Crop logic -----
  bool soilOK = (soilValue >= soilMin && soilValue <= soilMax);
  bool tempOK = (t >= tempMin && t <= tempMax);
  bool humOK  = (h >= humMin && h <= humMax);

  if (soilOK && tempOK && humOK) {
    // All conditions good
    digitalWrite(relayPin, LOW);    // Pump off
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Chinese Spinach OK ");
  } else {
    // Any condition wrong
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);

    // Soil control (pump)
    if (soilValue > soilMax) {
      digitalWrite(relayPin, HIGH);  // Pump ON
      lcd.setCursor(0, 1);
      lcd.print("Soil Dry: Pump On  ");
    } else if (soilValue < soilMin) {
      digitalWrite(relayPin, LOW);   // Soil too wet
      lcd.setCursor(0, 1);
      lcd.print("Soil Wet: Pump Off ");
    } else if (!tempOK) {
      lcd.setCursor(0, 1);
      lcd.print("Temp Alert!        ");
    } else if (!humOK) {
      lcd.setCursor(0, 1);
      lcd.print("Humidity Alert!    ");
    }
  }

  delay(2000);
}
