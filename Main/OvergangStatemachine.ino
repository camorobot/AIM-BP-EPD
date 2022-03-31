
void buttonNoordLogic(){
  // kijk of de trein er is. voer dan geen code uit.
  if (treinIsBezig) {

    //1. check of zuid groen heeft.
  } else if (buttonsPressed[2] == 1) {
    Serial.println("Zuid heeft al groen");
    // zuid heeft groen op dit moment.
  } else {
    // zuid heeft geen groen op dit moment.
    // dus noord kan direct op groen gaan.
    timerButtonNoordPressedEnteryCurrent = millis();
    timerButtonNoordPressedEntryIsBezig = true;
    timerButtonNoordPressedEntryCurrentLightGreen = true;
    // zet noord op groen, en zuid op rood.
    ledControlSetLedOff(leds[1], leds[3]);
    ledControlSetLedOn(leds[1], leds[0]);
  }
}


void buttonZuidLogic(){
  // kijk of de trein er is. voer dan geen code uit.
  if (treinIsBezig) {

    //1. check of noord groen heeft.
  } else if (buttonsPressed[0] == 1) {
    Serial.println("Noord heeft al groen");
    // noord heeft groen op dit moment.
    // maak timer die kijkt wanneer de noord het licht op rood heeft
  } else {
    // noord heeft geen groen op dit moment.
    // dus zuid kan direct op groen gaan.
    timerButtonZuidPressedEnteryCurrent = millis();
    timerButtonZuidPressedEntryIsBezig = true;
    timerButtonZuidPressedEntryCurrentLightGreen = true;
    // zet zuid op groen, en noord op rood.
    ledControlSetLedOff(leds[0], leds[0]);
    ledControlSetLedOn(leds[4], leds[3]);
  }
}

void buttonOostLogic(){
   // zet hier de status van de licht knoppen in een tijderelijke array *kan niet met een for loop ivm met andere lengthe van de arrays*
  buttonsPressedTemp[0] = buttonsPressed[0];
  buttonsPressedTemp[1] = buttonsPressed[2];
  //1. check of de trein vanaf west kwam
  if (buttonsPressed[3] == 1) {
    treinIsBezig = false;
    treinIsNetWeg = true;
    treinIsNetWegRunOnce = true;
    // De trein kwam vanuit west
    // nu kunnen we de lampen weer aan laten gaan.
    // 1 krijg lampen van de array
    // 2 zet lampen aan
    // 3 reset de oost knop
    Serial.println("buttonOostPressedEntry - De trein kwam vanaf west");
    // reset de west knop
    //    buttonsPressed[3] = 0;
//    if (buttonsPressedTemp[0] == 1) {
//      Serial.println("buttonOostPressedEntry -> buttonNoordPressedEntry");
//      buttonNoordPressedEntry();
//    } else if (buttonsPressedTemp[2] == 1) {
//      Serial.println("buttonOostPressedEntry -> buttonZuidPressedEntry");
//      buttonZuidPressedEntry();
//    }
  } else {
    treinIsBezig = true;
    // De trein kwam vauit oost
    // zet de lamp noord direct op geel en rood.
    if (timerButtonNoordPressedEntryCurrentLightGreen) {
      timerButtonNoordPressedEnteryCurrent = millis();
      timerButtonNoordPressedEntryIsBezig = true;
      ledControlSetLedOff(leds[1], leds[3]);
      ledControlSetLedOn(leds[2], leds[2]);
      // er komt een trein aan, de oranje lamp kan na 2 sec beginnen met knipperen
    }
    else if (timerButtonZuidPressedEntryCurrentLightGreen) {
      timerButtonZuidPressedEnteryCurrent = millis();
      timerButtonZuidPressedEntryIsBezig = true;
      ledControlSetLedOff(leds[0], leds[4]);
      ledControlSetLedOn(leds[5], leds[5]);
    }
    else if (buttonsPressed[0] == 1 && buttonsPressed[3] == 1) {
      Serial.println("zet de lampen van noord direct op geel en rood");
      ledControlSetLedOff(leds[1], leds[3]);
      ledControlSetLedOn(leds[2], leds[2]);
      //      timerButtonNoordPressedEnteryCurrent = millis();
      timerButtonNoordPressedEntryIsBezig = true;
      timerButtonNoordPressedEntryCurrentLightGreen = true;
      //      zet de lamp zuid direct op geel en rood
    } else if (buttonsPressed[2] == 1 && buttonsPressed[1] == 0) {
      Serial.println("zet de lampen van zuid direct op geel en rood");
      ledControlSetLedOff(leds[4], leds[0]);
      ledControlSetLedOn(leds[5], leds[5]);
      //      timerButtonZuidPressedEnteryCurrent = millis();
      timerButtonZuidPressedEntryIsBezig = true;
      timerButtonZuidPressedEntryCurrentLightGreen = true;
    }
  }
}


void buttonWestLogic(){
  // zet hier de status van de licht knoppen in een tijderelijke array *kan niet met een for loop ivm met andere lengthe van de arrays*
  buttonsPressedTemp[0] = buttonsPressed[0];
  buttonsPressedTemp[1] = buttonsPressed[2];
  //1. check of de trein vanaf oost kwam
  if (buttonsPressed[1] == 1) {
    treinIsBezig = false;
    treinIsNetWeg = true;
    treinIsNetWegRunOnce = true;
    // reset de oost knop
    //    buttonsPressed[1] = 0;
    Serial.println("De trein kwam vanaf oost");
    // De trein kwam vanuit oost
    // Doe hier de logica van het opheffen van de trein.
    // als noord had gedrukt mag noord eerst.
//    if (buttonsPressedTemp[0] == 1) {
//      Serial.println("buttonWestPressedEntry -> buttonNoordPressedEntry");
//      buttonNoordPressedEntry();
//    } else if (buttonsPressedTemp[2] == 1) {
//      Serial.println("buttonWestPressedEntry -> buttonZuidPressedEntry");
//      buttonZuidPressedEntry();
//    }
  } else {
    treinIsBezig = true;
    Serial.println("buttonWestPressedEntry - De trein kwam vanuit west");
    // De trein kwam vauit west
    // zet de lamp noord direct op geel en rood.
    if (timerButtonNoordPressedEntryCurrentLightGreen) {
      timerButtonNoordPressedEnteryCurrent = millis();
      timerButtonNoordPressedEntryIsBezig = true;
      ledControlSetLedOff(leds[1], leds[3]);
      ledControlSetLedOn(leds[2], leds[2]);
    }
    else if (timerButtonZuidPressedEntryCurrentLightGreen) {
      timerButtonZuidPressedEnteryCurrent = millis();
      timerButtonZuidPressedEntryIsBezig = true;
      ledControlSetLedOff(leds[0], leds[4]);
      ledControlSetLedOn(leds[5], leds[5]);
    }
    else if (buttonsPressed[0] == 1 && buttonsPressed[1] == 1) {
      Serial.println("zet de lampen van noord direct op geel en rood");
      ledControlSetLedOff(leds[1], leds[3]);
      ledControlSetLedOn(leds[2], leds[2]);
      //      timerButtonNoordPressedEnteryCurrent = millis();
      timerButtonNoordPressedEntryIsBezig = true;
      timerButtonNoordPressedEntryCurrentLightGreen = true;
      //      zet de lampen zuid direct op geel en rood
    } else if (buttonsPressed[2] == 1 && buttonsPressed[1] == 1) {
      Serial.println("zet de lampen van zuid direct op geel en rood");
      ledControlSetLedOff(leds[4], leds[0]);
      ledControlSetLedOn(leds[5], leds[5]);
      //      timerButtonZuidPressedEnteryCurrent = millis();
      timerButtonZuidPressedEntryIsBezig = true;
      timerButtonZuidPressedEntryCurrentLightGreen = true;
    } else if (buttonsPressed[0] == 0) {
      // hier even naar kijken want is onzeker of niet wel helemaal goed gaat.
    }
  }
}

void resetCompleteEntry(){
  for(int buttonNumberInArray = 0; buttonNumberInArray < AANTAL_BUTTONS; buttonNumberInArray++){
    setButtonsPressed(buttonNumberInArray, false);
  }
  for(int ledsNumberInArray = 0; ledsNumberInArray < AANTAL_LEDS; ledsNumberInArray++){
    ledControlSetLedOff(leds[2],leds[5]);
    ledControlSetLedOff(leds[1],leds[4]);
  }
}
