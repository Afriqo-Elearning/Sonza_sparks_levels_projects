#include <LiquidCrystal.h>
#include <DHT.h>
#include <SoftwareSerial.h>

// LCD setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int moisture_threshold = 500;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// DHT22 setup
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Soil sensor + relay
#define SOIL_PIN A0
#define RELAY_PIN 6

// SoftwareSerial to Xiao ESP32-C6
SoftwareSerial mySerial(9, 10); // RX=9, TX=10

// Display cycle
unsigned long lastDisplay = 0;
int displayState = 0; // 0=temp+hum, 1=soil, 2=relay

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  lcd.begin(16, 2);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  lcd.print("Smart Farming");
  delay(2000);
  lcd.clear();

  Serial.println("System initialized...");
}

void loop() {
  // Read sensors
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int soilValue = analogRead(SOIL_PIN);

  if (isnan(h) || isnan(t)) {
    Serial.println("DHT sensor error!");
    lcd.setCursor(0, 0);
    lcd.print("DHT Error!   ");
  }

  // Send data to Xiao
  mySerial.print("T:");
  mySerial.print(t);
  mySerial.print(" H:");
  mySerial.print(h);
  mySerial.print(" S:");
  mySerial.print(soilValue);
  mySerial.print(" R:");
  mySerial.println(digitalRead(RELAY_PIN));

  Serial.print("Temp: "); Serial.print(t);
  Serial.print(" °C | Hum: "); Serial.print(h);
  Serial.print(" % | Soil: "); Serial.print(soilValue);
  Serial.print(" | Relay: "); Serial.println(digitalRead(RELAY_PIN));

  // Check if Xiao sent command
  if (mySerial.available()) {
    char cmd = mySerial.read();
    if (cmd == '1') {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Relay ON (Manual Watering)");
    } else if (cmd == '0') {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("Relay OFF (Manual Stop)");
    }
  }

  if(soilValue  <  moisture_threshold){
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Relay ON (Auto watering ON)");
  }else{
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Relay OFF (Auto watering OFF)");
  }

  // Handle LCD display cycle every 60s
  if (millis() - lastDisplay > 2000) {
    lastDisplay = millis();
    lcd.clear();

    if (displayState == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Temp: "); lcd.print(t, 1); lcd.print((char)223); lcd.print("C");
      lcd.setCursor(0, 1);
      lcd.print("Hum:  "); lcd.print(h, 1); lcd.print("%");
      Serial.println("LCD: Showing Temp & Humidity");
    }
    else if (displayState == 1) {
      lcd.setCursor(0, 0);
      lcd.print("Soil Moisture:");
      lcd.setCursor(0, 1);
      lcd.print(soilValue);
      Serial.println("LCD: Showing Soil Moisture");
    }
    else if (displayState == 2) {
      lcd.setCursor(0, 0);
      lcd.print("Waterpump State:");
      lcd.setCursor(0, 1);
      lcd.print(digitalRead(RELAY_PIN) ? "ON " : "OFF");
      Serial.println("LCD: Showing Relay State");
    }

    displayState = (displayState + 1) % 3; // loop between 0-2
  }

  delay(2000); // sensor read delay
}
