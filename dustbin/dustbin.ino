#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 8
#define SERVO_PIN 3
#define GREEN_LED 5
#define RED_LED 6
#define BUZZER 7

Servo lidServo;

long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distanceCM = duration * 0.034 / 2;

  return distanceCM;
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lidServo.attach(SERVO_PIN);
  lidServo.write(0);  // Lid closed at start

  digitalWrite(RED_LED, HIGH);   // Red ON at idle
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER, LOW);
}

void loop() {
  long distance = readDistanceCM();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 20) {
    // Person detected - open lid if not already open
    lidServo.write(90);  // Open
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    // Beep once when detected
    digitalWrite(BUZZER, HIGH);
    delay(300);
    digitalWrite(BUZZER, LOW);

    // Wait until person moves away
    while (readDistanceCM() < 20) {
      delay(1000); // check every 100ms
    }

    lidServo.write(0);  // Close
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  } else {
    // Nothing near
    lidServo.write(0);  // Ensure closed
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, LOW);
  }

  delay(200);
}
