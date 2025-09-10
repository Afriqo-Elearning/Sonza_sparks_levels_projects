#include <SoftwareSerial.h>

// Bluetooth setup (RX, TX)
SoftwareSerial BT(2, 3); // RX, TX

// Motor A pins
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B pins
int enB = 10;
int in3 = 5;
int in4 = 4;

unsigned long lastCommandTime = 0;
int commandTimeout = 300;  // time in milliseconds before auto-stop
char currentCommand = '0';

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  analogWrite(enA, 200);
  analogWrite(enB, 200);

  Serial.begin(9600);
  BT.begin(9600);
}

void loop() {
  if (BT.available()) {
    currentCommand = BT.read();
    lastCommandTime = millis();  // update last time command was received

    Serial.print("Received: ");
    Serial.println(currentCommand);
  }

  // Check if command timed out
  if (millis() - lastCommandTime > commandTimeout) {
    stopMotors(); // stop if no command received recently
    currentCommand = '0';
    return;
  }

  switch (currentCommand) {
    case '1':
      moveForward();
      break;
    case '2':
      moveBackward();
      break;
    case '3':
      turnLeft();
      break;
    case '4':
      turnRight();
      break;
    case '0':
    default:
      stopMotors();
      break;
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
