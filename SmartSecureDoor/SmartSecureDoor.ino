#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <avr/wdt.h>

#define SS_PIN 10
#define RST_PIN 9  

#define RedLed 4
#define GreenLed 3
#define buzzer 2
#define servoPin 7
#define ledr A0   // LDR pin for laser detection

bool doorOpen = false;

MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;

int threshold = 40; // Laser break detection threshold
const String Correct_card = "183EDF59";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  wdt_enable(WDTO_2S);  // Enable watchdog timer

  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledr, INPUT); // LDR input pin

  myServo.attach(servoPin);
  closeDoor();

  Serial.println("Ready...");
}

void loop() {
  wdt_reset();

  // 🚨 Laser security check
  checkLaserSecurity();

  // RFID check
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  String id = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    id += String(rfid.uid.uidByte[i], HEX);
  }
  id.toUpperCase();

  Serial.println("UID: " + id);

  if (id == Correct_card) {
    successSound(); 
    digitalWrite(GreenLed, HIGH);
    delay(500);
    digitalWrite(GreenLed, LOW);

    openDoor();  // Open the door
    for (int i = 0; i < 10; i++) {
      delay(500);
      wdt_reset();
    }
    closeDoor(); // Close it

  } else {
    digitalWrite(RedLed, HIGH);  
    warningSound();
    delay(500);
    digitalWrite(RedLed, LOW);
    Serial.println("Incorrect card");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void checkLaserSecurity() {
  int laserValue = analogRead(ledr);
  Serial.print("Laser Value: ");
  Serial.println(laserValue);

  if (laserValue > threshold) {
    Serial.println("Laser broken! Security breach!");
    digitalWrite(RedLed, HIGH);

    // 🔔 Beep continuously for 5 seconds
    unsigned long start = millis();
    while (millis() - start < 3000) {
      tone(buzzer, 600);
      delay(100);  // small delay to allow watchdog to reset
      wdt_reset(); // keep watchdog happy
    }
    noTone(buzzer);
    digitalWrite(RedLed, LOW);

    // Optionally lock door if open
    if (doorOpen) {
      closeDoor();
      Serial.println("Door closed due to breach!");
    }
  }
}

void warningSound() {
  tone(buzzer, 500, 500);
  delay(500);
  noTone(buzzer);
}

void successSound() {
  tone(buzzer, 1000, 300);
  delay(300);
  noTone(buzzer);
  tone(buzzer, 1500, 300);
  delay(300);
  noTone(buzzer);
}

void closeDoor() {
  myServo.write(0);
  doorOpen = false;
  Serial.println("Door CLOSED");
}

void openDoor() {
  myServo.write(180);
  doorOpen = true;
  Serial.println("Door OPEN");
}
