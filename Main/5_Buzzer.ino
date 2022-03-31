
int buzzerPin = A1;
int buzzerDelay = 100;
unsigned long buzzerPreviousMillis;
unsigned long buzzerPreviousMillisBeep3;
unsigned long buzzerPreviousMillisBeep3Timeout;
int buzzerDelay3Beeps = 1250;
int aantalBeeps3 = 4;
boolean buzzerBeep3IsRunning = false;

void buzzerSetup() {
  pinMode(buzzerPin, OUTPUT);
}

void buzzerBeep() {
  if (millis() - buzzerPreviousMillis >= buzzerDelay) {
    buzzerPreviousMillis = millis();
    if (digitalRead(buzzerPin) == HIGH) {
      noTone(buzzerPin);
    } else {
      tone(buzzerPin, 50);
    }
  }
}

void buzzerBeep3(){
  if (buzzerBeep3IsRunning && (millis() - buzzerPreviousMillisBeep3 >= buzzerDelay - 15)) {
    buzzerPreviousMillisBeep3 = millis();
    noTone(buzzerPin);
    if(aantalBeeps3 <= 0){
      if (millis() - buzzerPreviousMillisBeep3Timeout >= buzzerDelay3Beeps) {
        noTone(buzzerPin);
        buzzerPreviousMillisBeep3Timeout = millis();
        aantalBeeps3 = 4;
      }
    } else {
      if (digitalRead(buzzerPin) == HIGH) {
        noTone(buzzerPin);
      } else {
        tone(buzzerPin,50);
        aantalBeeps3--;
      }
    }
  }
}

void buzzerStop() {
  // deley moest erin anders bleef die vaak nog door beepen ookal was de methode aangeroepen
  if (millis() - buzzerPreviousMillis >= buzzerDelay) {
    buzzerPreviousMillis = millis();
    noTone(buzzerPin);
  }
}

void setBuzzerBeep3IsRunning(boolean state){
  buzzerBeep3IsRunning = state;
}
