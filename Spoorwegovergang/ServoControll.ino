#include <Servo.h>
//
//// Attributes
Servo servo;
const int SERVOPIN = 13;
const int SERVO_START_POS = 0;
const int SERVO_TIME_INTERVAL = 80; // ms
const int SERVO_STEP_SIZE = 1;
const int SLAGBOOM_IS_BENEDEN = 89;

int servoAantalKeerGeopent;
int servoCurrentPos = 0;
unsigned long servoPreviousMillis = 0;
//
//// Methods
void servoControllSetup() {
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

//
//int getServoCurrentPos() {
//  return servoCurrentPos;
//}
//
//int getSlagboomBenenden() {
//  return SLAGBOOM_IS_BENEDEN;
//}

int getServoAantalKeerGeopent() {
  return servoAantalKeerGeopent;
}

void setServoAantalKeerGeopent() {
  servoAantalKeerGeopent++;
}

void setResetServoAantalKeerGeopent(){
  servoAantalKeerGeopent = 0;
  Serial.print("De slagboom is ");
  Serial.print("0");
  Serial.println(" aantal keer geopent.");
}
