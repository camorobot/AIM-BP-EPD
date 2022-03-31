
const int BUZZERPIN = A1;
const int BUZZERDELAY = 100;
unsigned long buzzerPreviousMillis;
unsigned long buzzerPreviousMillisBeep3;
unsigned long buzzerPreviousMillisBeep3Timeout;
const int BUZZERDELAYBEEPS3 = 1250;
int aantalBeeps3 = 4;
boolean buzzerBeep3IsRunning = false;

void buzzerSetup() {
  pinMode(BUZZERPIN, OUTPUT);
}

void buzzerBeep() {
  if (millis() - buzzerPreviousMillis >= BUZZERDELAY) {
    buzzerPreviousMillis = millis();
    if (digitalRead(BUZZERPIN) == HIGH) {
      noTone(BUZZERPIN);
    } else {
      tone(BUZZERPIN, 50);
    }
  }
}

void buzzerBeep3(){
  if (buzzerBeep3IsRunning && (millis() - buzzerPreviousMillisBeep3 >= BUZZERDELAY - 15)) {
    buzzerPreviousMillisBeep3 = millis();
    noTone(BUZZERPIN);
    if(aantalBeeps3 <= 0){
      if (millis() - buzzerPreviousMillisBeep3Timeout >= BUZZERDELAYBEEPS3) {
        noTone(BUZZERPIN);
        buzzerPreviousMillisBeep3Timeout = millis();
        aantalBeeps3 = 4;
      }
    } else {
      if (digitalRead(BUZZERPIN) == HIGH) {
        noTone(BUZZERPIN);
      } else {
        tone(BUZZERPIN,50);
        aantalBeeps3--;
      }
    }
  }
}

void buzzerStop() {
  // deley moest erin anders bleef die vaak nog door beepen ookal was de methode aangeroepen
  if (millis() - buzzerPreviousMillis >= BUZZERDELAY) {
    buzzerPreviousMillis = millis();
    noTone(BUZZERPIN);
  }
}

void setBuzzerBeep3IsRunning(boolean state){
  buzzerBeep3IsRunning = state;
}
