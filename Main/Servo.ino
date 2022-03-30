#include <Servo.h>

// Attributes
Servo servo;
const int SERVOPIN = A0;
const int SERVO_START_POS = 0;
const int SERVO_TIME_INTERVAL = 40; // ms
const int SERVO_STEP_SIZE = 1;

int servoCurrentPos = 0;
unsigned long servoPreviousMillis = 0;

// Methods
void servoSetup() {
  servo.attach(SERVOPIN);
  servoPreviousMillis = millis();
  servo.write(SERVO_START_POS);
}

void moveServo( int goalPos ) {
  if (millis() - servoPreviousMillis >= SERVO_TIME_INTERVAL) {
    if (servoCurrentPos < goalPos) {
      servo.write(servo.read() + SERVO_STEP_SIZE);
      servoCurrentPos = servo.read();
    } else if (servoCurrentPos > goalPos) {
      servo.write(servo.read() - SERVO_STEP_SIZE);
      servoCurrentPos = servo.read();
    }
    servoPreviousMillis = millis();
  }
}

int getServoCurrentPos() {
  return servoCurrentPos;
}
