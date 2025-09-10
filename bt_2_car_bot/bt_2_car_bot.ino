#include <Servo.h>
/**
 *      One Day Of Code
 * Arduino Car - Example code
 *      Board: Arduino
 *  Control Bluetooth Serial
 */

// Pins to use
int PIN_SERVO_A = 2;
int PIN_SERVO_B = 3;

// Left tires
int PIN_IN1 = 7;
int PIN_IN2 = 6;

// Right tires
int PIN_IN3 = 8;
int PIN_IN4 = 9;

// Led/Light
int PIN_LED = 5;
int PIN_LED_2 = 4;

// Distance sensor HC-SR04
int PIN_ECHO = 10;
int PIN_TRIG = 11;

// Servos
Servo servoA;
Servo servoB;

void setup() {

    // Init serial
    Serial.begin(9600);
    Serial.setTimeout(5);

    // Config pins
    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, OUTPUT);
    pinMode(PIN_IN3, OUTPUT);
    pinMode(PIN_IN4, OUTPUT);

    // Init servo
    servoA.attach(PIN_SERVO_A);
    servoB.attach(PIN_SERVO_B);

    // Init led/light
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_LED_2, OUTPUT);

    // Init distance sensor
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);

}

void loop() {

    char codeReceived;
    String numericPart = "";

    while (Serial.available() > 0) {
        String line = Serial.readString();
        for (int i = 0; i < line.length(); i++) {
            int character = line[i];
            if (isDigit(character)) {
                numericPart += (char) character;
            } else if (character != '\n') {
                codeReceived = character;
            } else {
                break;
            }
        }
    }

    switch (codeReceived) {
        case 'F': goForward(); break;
        case 'L': turnLeft(); break;
        case 'B': goBack(); break;
        case 'R': turnRight(); break;
        case 'S': stop(); break;
        case 'M': turnOnLed(); break;
        case 'm': turnOffLed(); break;
        case 'N': turnOnLed2(); break;
        case 'n': turnOffLed2(); break;
        case 'J':
            if (numericPart != "") {
                rotateServoA(numericPart.toInt());
            }
            break;
        case 'K':
            if (numericPart != "") {
                rotateServoB(numericPart.toInt());
            }
            break;
    }

    Serial.print("D");
    Serial.println(measureDistance());

    delay(10);
}

long measureDistance() {
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    long duration = pulseIn(PIN_ECHO, HIGH);

    return microsecondsToCentimeters(duration);
}

long microsecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
}

void turnOnLed() {
    digitalWrite(PIN_LED, HIGH);
}

void turnOffLed() {
    digitalWrite(PIN_LED, LOW);
}

void turnOnLed2() {
    digitalWrite(PIN_LED_2, HIGH);
}

void turnOffLed2() {
    digitalWrite(PIN_LED_2, LOW);
}

void rotateServoA(int grados) {
    servoA.write(grados);
}

void rotateServoB(int grados) {
    servoB.write(grados);
}

void goForward() {
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);

    digitalWrite(PIN_IN3, HIGH);
    digitalWrite(PIN_IN4, LOW);
}

void goBack() {
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, HIGH);

    digitalWrite(PIN_IN3, LOW);
    digitalWrite(PIN_IN4, HIGH);
}

void stop() {
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, LOW);

    digitalWrite(PIN_IN3, LOW);
    digitalWrite(PIN_IN4, LOW);
}

void turnLeft() {
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, HIGH);

    digitalWrite(PIN_IN3, HIGH);
    digitalWrite(PIN_IN4, LOW);
}

void turnRight() {
    digitalWrite(PIN_IN3, LOW);
    digitalWrite(PIN_IN4, HIGH);

    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);
}
