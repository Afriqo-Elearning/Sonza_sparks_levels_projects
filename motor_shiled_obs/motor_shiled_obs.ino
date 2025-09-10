#include <AFMotor.h>

// Motors on M1 and M2
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);

const int wait = 600;

void setup() {
  Serial.begin(9600);
  Serial.println("Robot walking test...");

  motor1.setSpeed(200);   // speed 0–255
  motor2.setSpeed(200);
  motor3.setSpeed(200);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  delay(1000);
}

void loop() {
  // Step 1: Left leg forward, right leg on ground
  Serial.println("Step: Left forward");
  motor1.run(FORWARD);   // lift/move leg 1
  motor2.run(RELEASE);   // keep leg 2 stable (touch ground)
  delay(wait);

  // // Step 2: Right leg forward, left leg on ground
  // Serial.println("Step: Right forward");
  motor1.run(RELEASE);   // keep leg 1 stable
  motor2.run(FORWARD);   // lift/move leg 2
  delay(wait);

  // Repeat
}
