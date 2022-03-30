boolean timerButtonNoordPressedEntryCurrentLightGreen = false;
boolean timerButtonNoordPressedEntryCurrentLightYellow = false;
boolean timerButtonNoordPressedEntryCurrentLightRed = false;
boolean timerButtonZuidPressedEntryCurrentLightGreen = false;
boolean timerButtonZuidPressedEntryCurrentLightYellow = false;
boolean timerButtonZuidPressedEntryCurrentLightRed = false;
boolean timerButtonNoordPressedEntryIsBezig = false;
boolean timerButtonZuidPressedEntryIsBezig = false;
boolean ontruimingstijd;
boolean treinIsNetWeg;
boolean treinIsBezig;

const int timerButtonPressedEntryDelay = 2000;
const int ontruimingstijdDelay = 2000;

unsigned long timerButtonNoordPressedEnteryCurrent = 0;
unsigned long timerButtonZuidPressedEnteryCurrent = 0;
unsigned long ontruimingstijdCurrent = 0;

void timerSetup() {
  timerButtonNoordPressedEntryIsBezig = false;
  timerButtonZuidPressedEntryIsBezig = false;
  ontruimingstijd = false;
  treinIsBezig = false;
  treinIsNetWeg = false;
}

void timerLoop() {
  //  // word alleen aangeroepen als er een trein is.
  //  if (treinIsBezig) {
  //    ledControlLedsBlink(leds[2], leds[5]);
  //  }
  // zet de gele knipper licht uit nadat de trein weg is.
  if ((treinIsNetWeg && getLedStatus(2) == HIGH) || (treinIsNetWeg && getLedStatus(5) == HIGH)) {
    ledControlSetLedOff(leds[2], leds[5]);
  }

  if ((treinIsBezig && getLedStatus(3) == HIGH && getLedStatus(0) == HIGH)) {
    ledControlLedsBlink(leds[2], leds[5]);
  }

  // Timer voor het aanroepen van de stoplichten noord van groen -> geel
  if (timerButtonNoordPressedEntryIsBezig && timerButtonNoordPressedEntryCurrentLightGreen && ((millis() - timerButtonNoordPressedEnteryCurrent) >= timerButtonPressedEntryDelay)) {
    Serial.println("fakka we zijn net voor een keuze maken van groen of geel");
    if (timerButtonNoordPressedEntryCurrentLightGreen) {
      // draai hier een timer voor 2 sec en verander het licht naar geel
      Serial.println("Zet de lampen op geel na 2 seconden...");
      // zet de lamp van noord op geel
      ledControlSetLedOff(leds[1], leds[0]);
      ledControlSetLedOn(leds[2], leds[0]);
      timerButtonNoordPressedEntryCurrentLightGreen = false;
      timerButtonNoordPressedEntryCurrentLightYellow = true;
      timerButtonNoordPressedEnteryCurrent = millis();
    }
  }
  // Timer voor het aanroepen van de stoplichten noord van geel -> rood
  if (timerButtonNoordPressedEntryIsBezig && timerButtonNoordPressedEntryCurrentLightYellow && ((millis() - timerButtonNoordPressedEnteryCurrent) >= timerButtonPressedEntryDelay)) {
    // draai hier een timer voor 2 sec en verander het licht naar geel
    Serial.println("Zet de lampen op rood na 2 seconden...");
    // zet de lamp van noord op rood
    ledControlSetLedOff(leds[2], leds[0]);
    ledControlSetLedOn(leds[3], leds[0]);
    timerButtonNoordPressedEnteryCurrent = millis();
    timerButtonNoordPressedEntryCurrentLightYellow = false;
    timerButtonNoordPressedEntryCurrentLightRed = true;
    buttonsPressed[0] = 0;
    // start de ontruimingstimer
    ontruimingstijdCurrent = millis();
    ontruimingstijd = true;
  }
  // Timer voor het aanroepen van de stoplichten zuid van groen -> geel
  if (timerButtonZuidPressedEntryIsBezig && timerButtonZuidPressedEntryCurrentLightGreen && ((millis() - timerButtonZuidPressedEnteryCurrent) >= timerButtonPressedEntryDelay)) {
    Serial.println("fakka we zijn net voor een keuze maken van groen of geel");
    if (timerButtonZuidPressedEntryCurrentLightGreen) {
      // draai hier een timer voor 2 sec en verander het licht naar geel
      Serial.println("Zet de lampen op geel na 2 seconden...");
      // zet de lamp van zuid op geel
      ledControlSetLedOff(leds[4], leds[4]);
      ledControlSetLedOn(leds[5], leds[5]);
      timerButtonZuidPressedEntryCurrentLightGreen = false;
      timerButtonZuidPressedEntryCurrentLightYellow = true;
      timerButtonZuidPressedEntryCurrentLightRed = false;
      timerButtonZuidPressedEnteryCurrent = millis();
    }
  }
  // Timer voor het aanroepen van de stoplichten zuid van geel -> rood
  if (timerButtonZuidPressedEntryIsBezig && timerButtonZuidPressedEntryCurrentLightYellow && ((millis() - timerButtonZuidPressedEnteryCurrent) >= timerButtonPressedEntryDelay)) {
    // draai hier een timer voor 2 sec en verander het licht naar geel
    Serial.println("Zet de lampen zuid op rood na 2 seconden...");
    // zet de lamp van zuid op rood
    ledControlSetLedOff(leds[5], leds[5]);
    ledControlSetLedOn(leds[0], leds[0]);
    timerButtonZuidPressedEnteryCurrent = millis();
    timerButtonZuidPressedEntryCurrentLightYellow = false;
    timerButtonZuidPressedEntryCurrentLightRed = true;
    timerButtonZuidPressedEntryIsBezig = false;
    buttonsPressed[2] = 0;
    // start de ontruimingstimer
    ontruimingstijdCurrent = millis();
    ontruimingstijd = true;
  }
  // Timer voor het aanroepen van de stoplichten nog 2 seconden op rood blijven voor de ontruiming.
  if (ontruimingstijd && ((millis() - ontruimingstijdCurrent) >= ontruimingstijdDelay)) {
    ontruimingstijd = false;
    if (buttonsPressed[0] == 1) {
      buttonNoordPressedEntry();
    } else if (buttonsPressed[2] == 1) {
      buttonZuidPressedEntry();
    }
  }

  // timer / logica voor het opnieuw aanroepen van de lichten als de trein net weg is.
  if (!treinIsBezig && treinIsNetWeg) {
    Serial.println("Timer / Logic van treinNetWeg word gerunt.");
    treinIsNetWeg = false;
    // reset de knoppen van de trein overgang. (oost & west)
    buttonsPressed[1] = 0;
    buttonsPressed[3] = 0;
    if (buttonsPressedTemp[0] == 1) {
      Serial.println("De lampen van noord moeten aan.");
      buttonsPressedTemp[0] = 0;
      buttonNoordPressedEntry();
    } else if (buttonsPressedTemp[1] == 1) {
      Serial.println("De lampen van zuid moeten aan.");
      buttonsPressedTemp[1] = 0;
      buttonZuidPressedEntry();
    }
  }
}
