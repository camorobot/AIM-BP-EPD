#include <Servo.h>

// Attributes
Servo servo;
const int SERVOPIN = 13;
const int SERVO_START_POS = 0;
const int SERVO_TIME_INTERVAL = 40; // ms
const int SERVO_STEP_SIZE = 5;
const int SLAGBOOM_IS_BENEDEN = 90;

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
    } else if (treinIsNetWeg && (servoCurrentPos == goalPos)) {
      // deze vals moet nog op true blijven anders gaan de lichten weer aan op het moment dat de trein weg is !!!! eerst moet de timer van de display naar 0 gaan
      //      treinIsNetWeg = false;
      displayTimerIsRunning = true;
      buzzerStop();
      buzzerBeep3();
      buzzerBeep3IsRunning = true;
      if (displayTimerIsRunningDone) {
        knipperenIsBezig = false;
        displayTimerIsRunningDone = false;
        displayTimerIsRunning = false;
        buzzerStop();
        buzzerBeep3IsRunning = false;
        resetCompleteEntry();
        Serial.println("Als het goed is kan dit niet in een loop zitten");
      } 
      // nu moet het aftellen starten van de display en de buzzer moet 3 tikken doen en een pauze
      // 1 start de display van 5 naar 0
      // 2 buzzerBeep3() moet tegelijk afgaan.
    } else if (servoCurrentPos == goalPos) {
      buzzerStop();
    }
    buzzerBeep();
    servoPreviousMillis = millis();
  }
}

int getServoCurrentPos() {
  return servoCurrentPos;
}

int getSlagboomBenenden() {
  return SLAGBOOM_IS_BENEDEN;
}

void l() {
  Serial.println(servo.read());
}
