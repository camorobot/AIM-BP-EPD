
const int BUZZERPIN = A1;
const int BUZZERDELAY = 200;
unsigned long buzzerPreviousMillis;
unsigned long buzzerPreviousMillisBeep3;
unsigned long buzzerPreviousMillisBeep3Timeout;
const int BUZZERDELAYBEEPS3 = 2000;
int aantalBeeps3 = 1;
boolean buzzerBeep3IsRunning = false;

void buzzerControllSetup() {
  pinMode(BUZZERPIN, OUTPUT);
}

void buzzerBeep() {
  if (millis() - buzzerPreviousMillis >= BUZZERDELAY) {
    buzzerPreviousMillis = millis();
    if (digitalRead(BUZZERPIN) == HIGH) {
      digitalWrite(BUZZERPIN, LOW);
    } else {
      digitalWrite(BUZZERPIN, HIGH);
    }
  }
}

void buzzerBeep3(){
  if ((millis() - buzzerPreviousMillisBeep3 >= BUZZERDELAY)) {
    buzzerPreviousMillisBeep3 = millis();
    digitalWrite(BUZZERPIN, LOW);
    if(aantalBeeps3 <= 0){
      if (millis() - buzzerPreviousMillisBeep3Timeout >= BUZZERDELAYBEEPS3) {
        digitalWrite(BUZZERPIN, HIGH);
        buzzerPreviousMillisBeep3Timeout = millis();
        aantalBeeps3 = 1;
      }
    } else {
      aantalBeeps3--;
      if (digitalRead(BUZZERPIN) == HIGH) {
        digitalWrite(BUZZERPIN,LOW);
      } else {
        digitalWrite(BUZZERPIN,HIGH);
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
