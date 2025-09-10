#include "laser_security.h"

// Pin definitions
const int ldrPin     = A0;  // LDR analog input
const int buzzerPin  = 9; 
const int Red_led    = 10;    
const int Green_led  = 7;    

// Threshold for triggering alarm
int threshold = 40; // Adjust based on ambient light

// Initialize pins
void securityInit() {
    pinMode(ldrPin, INPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(Red_led, OUTPUT);
    pinMode(Green_led, OUTPUT);
    Serial.begin(9600);
}

// Check the LDR and trigger alarm if needed
void checkLaserSecurity() {
    int ldrValue = analogRead(ldrPin);
    Serial.print("Laser Value: ");
    Serial.println(ldrValue);

    if (ldrValue > threshold) {
        // Laser is blocked — run alert mode for 5 seconds
        unsigned long startTime = millis();
        digitalWrite(Green_led, LOW); // Turn off green while alerting

        while (millis() - startTime < 5000) {
            // Beep
            tone(buzzerPin, 1000);
            delay(300);
            noTone(buzzerPin);

            // Blink Red LED
            digitalWrite(Red_led, HIGH);
            delay(100);
            digitalWrite(Red_led, LOW);
            delay(100);
        }
    } else {
        noTone(buzzerPin);  
        digitalWrite(Red_led, LOW);
        digitalWrite(Green_led, HIGH);
    }
}
