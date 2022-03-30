
int buzzerDelay = 50;
unsigned long buzzerPreviousMillis;

void buzzerSetup() {
  pinMode(A1, OUTPUT);
}

void buzzerBeep () {
  if (millis() - buzzerPreviousMillis >= buzzerDelay) {
    buzzerPreviousMillis = millis();
    if (digitalRead(A1) == HIGH) {
      noTone(A1);
    } else {
      tone(A1, 50);
    }
  }
}

void buzzerStop() {
  // deley moest erin anders bleef die vaak nog door beepen ookal was de methode aangeroepen
  if (millis() - buzzerPreviousMillis >= buzzerDelay) {
    buzzerPreviousMillis = millis();
    noTone(A1);
  }
}
