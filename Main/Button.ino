// OvergangStateMachine VARS
// vars werden niet herkend in het tabblad overgangstatemachine
const int GEEN_KNOPPEN_GEDRUKT = 0;
const int VOETGANGER_NOORD = 1;
const int VOETGANGER_ZUID = 2;
const int TREIN_AANWEZIG = 3;

// Module Button
const int BUTTON_NOORD_STATE_RELEASED = 0;
const int BUTTON_NOORD_STATE_CHECK_PRESSED = 1;
const int BUTTON_NOORD_STATE_PRESSED = 2;
const int BUTTON_NOORD_STATE_CHECK_RELEASED = 3;
int buttonStateNoord;

const int BUTTON_OOST_STATE_RELEASED = 4;
const int BUTTON_OOST_STATE_CHECK_PRESSED = 5;
const int BUTTON_OOST_STATE_PRESSED = 6;
const int BUTTON_OOST_STATE_CHECK_RELEASED = 7;
int buttonStateOost;

const int BUTTON_ZUID_STATE_RELEASED = 8;
const int BUTTON_ZUID_STATE_CHECK_PRESSED = 9;
const int BUTTON_ZUID_STATE_PRESSED = 10;
const int BUTTON_ZUID_STATE_CHECK_RELEASED = 11;
int buttonStateZuid;

const int BUTTON_WEST_STATE_RELEASED = 12;
const int BUTTON_WEST_STATE_CHECK_PRESSED = 13;
const int BUTTON_WEST_STATE_PRESSED = 14;
const int BUTTON_WEST_STATE_CHECK_RELEASED = 15;
int buttonStateWest;

const int BUTTON_INTERVAL = 10;
unsigned long buttonPrevious;
boolean buttonClick;

int buttons[] = {A3, A5, A4, A2};
const int AANTAL_BUTTONS = 4;

void buttonSetup() {
  buttonStateNoord = BUTTON_NOORD_STATE_RELEASED;
  buttonStateZuid = BUTTON_ZUID_STATE_RELEASED;
  buttonStateOost = BUTTON_OOST_STATE_RELEASED;
  buttonStateWest = BUTTON_WEST_STATE_RELEASED;
}

int getButtonPressed(int buttonNumber) {
  return buttonsPressed[buttonNumber];
}

void buttonHardwareSetup() {
  for (int button = 0; button < AANTAL_BUTTONS; button++) {
    pinMode(buttons[button], INPUT);
  }
}

boolean buttonHardwareDown(int buttonNumber) {
  // Pull up resistor used.
  return (digitalRead(buttons[buttonNumber]) == HIGH);
  // if pull down resistor is used, compare to HIGH
}

boolean buttonHardwareUp(int buttonNumber) {
  return !buttonHardwareDown(buttonNumber);
}

boolean buttonClicked(int buttonNumber) {
  Serial.println("check Button Pressed: ");
  if (buttonsPressed[buttonNumber]) {
    // reset de waarde voor een nieuwe click
    buttonsPressed[buttonNumber] = false;
    return true;
  }
  else {
    return false;
  }
}

void buttonLoop() {
  switch (buttonStateNoord) {
    case BUTTON_NOORD_STATE_RELEASED:
      Serial.println("case: BUTTON_NOORD_STATE_RELEASED");
      if (buttonHardwareDown(0)) {
        Serial.println("check: ButtonHardwareDown[0]");
        buttonStateNoord = BUTTON_NOORD_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_NOORD_STATE_CHECK_PRESSED:
      Serial.println("case: BUTTON_NOORD_STATE_CHECK_PRESSED");
      if (buttonHardwareUp(0)) {
        Serial.println("Button false positive");
        buttonStateNoord = BUTTON_NOORD_STATE_RELEASED;
      }
      else if ((buttonHardwareDown(0)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        Serial.println("Button daadwerkelijk ingedrukt");
        buttonStateNoord = BUTTON_NOORD_STATE_PRESSED;
        buttonsPressed[0] = 1;
        buttonNoordPressedEntry();
      }
      break;
    case BUTTON_NOORD_STATE_PRESSED:
      Serial.println("case: BUTTON_NOORD_STATE_PRESSED");
      if (buttonHardwareUp(0)) {
        buttonStateNoord = BUTTON_NOORD_STATE_CHECK_RELEASED;
      }
      break;
    case BUTTON_NOORD_STATE_CHECK_RELEASED:
      if (buttonHardwareDown(0)) {
        buttonStateNoord = BUTTON_NOORD_STATE_PRESSED;
      }
      else if ((buttonHardwareUp(0)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        buttonStateNoord = BUTTON_NOORD_STATE_RELEASED;
      }
      break;
  }
  switch (buttonStateZuid) {
    case BUTTON_ZUID_STATE_RELEASED:
      Serial.println("case: BUTTON_ZUID_STATE_RELEASED");
      if (buttonHardwareDown(2)) {
        Serial.println("check: ButtonHardwareDown[2]");
        buttonStateZuid = BUTTON_ZUID_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_ZUID_STATE_CHECK_PRESSED:
      Serial.println("case: BUTTON_ZUID_STATE_CHECK_PRESSED");
      if (buttonHardwareUp(2)) {
        Serial.println("Button false positive");
        buttonStateZuid = BUTTON_ZUID_STATE_RELEASED;
      }
      else if ((buttonHardwareDown(2)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        Serial.println("Button daadwerkelijk ingedrukt");
        buttonStateZuid = BUTTON_ZUID_STATE_PRESSED;
        buttonsPressed[2] = 1;
        buttonZuidPressedEntry();
      }
      break;
    case BUTTON_ZUID_STATE_PRESSED:
      Serial.println("case: BUTTON_ZUID_STATE_PRESSED");
      if (buttonHardwareUp(2)) {
        buttonStateZuid = BUTTON_ZUID_STATE_CHECK_RELEASED;
      }
      break;
    case BUTTON_ZUID_STATE_CHECK_RELEASED:
      if (buttonHardwareDown(2)) {
        buttonStateZuid = BUTTON_ZUID_STATE_PRESSED;
      }
      else if ((buttonHardwareUp(2)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        buttonStateZuid = BUTTON_ZUID_STATE_RELEASED;
      }
      break;
  }
  switch (buttonStateOost) {
    case BUTTON_OOST_STATE_RELEASED:
      Serial.println("case: BUTTON_OOST_STATE_RELEASED");
      if (buttonHardwareDown(1)) {
        Serial.println("check: ButtonHardwareDown[1]");
        buttonStateOost = BUTTON_OOST_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_OOST_STATE_CHECK_PRESSED:
      Serial.println("case: BUTTON_OOST_STATE_CHECK_PRESSED");
      if (buttonHardwareUp(1)) {
        Serial.println("Button false positive");
        buttonStateOost = BUTTON_OOST_STATE_RELEASED;
      }
      else if ((buttonHardwareDown(1)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        Serial.println("Button daadwerkelijk ingedrukt");
        buttonStateOost = BUTTON_OOST_STATE_PRESSED;
        buttonsPressed[1] = 1;
        buttonOostPressedEntry();
      }
      break;
    case BUTTON_OOST_STATE_PRESSED:
      Serial.println("case: BUTTON_OOST_STATE_PRESSED");
      if (buttonHardwareUp(1)) {
        buttonStateOost = BUTTON_OOST_STATE_CHECK_RELEASED;
      }
      break;
    case BUTTON_OOST_STATE_CHECK_RELEASED:
      if (buttonHardwareDown(1)) {
        buttonStateOost = BUTTON_OOST_STATE_PRESSED;
      }
      else if ((buttonHardwareUp(1)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        buttonStateOost = BUTTON_OOST_STATE_RELEASED;
      }
      break;
  }
  switch (buttonStateWest) {
    case BUTTON_WEST_STATE_RELEASED:
      Serial.println("case: BUTTON_WEST_STATE_RELEASED");
      if (buttonHardwareDown(3)) {
        Serial.println("check: ButtonHardwareDown[3]");
        buttonStateWest = BUTTON_WEST_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_WEST_STATE_CHECK_PRESSED:
      Serial.println("case: BUTTON_WEST_STATE_CHECK_PRESSED");
      if (buttonHardwareUp(3)) {
        Serial.println("Button false positive");
        buttonStateWest = BUTTON_WEST_STATE_RELEASED;
      }
      else if ((buttonHardwareDown(3)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        Serial.println("Button daadwerkelijk ingedrukt");
        buttonStateWest = BUTTON_WEST_STATE_PRESSED;
        buttonsPressed[3] = 1;
        buttonWestPressedEntry();
      }
      break;
    case BUTTON_WEST_STATE_PRESSED:
      Serial.println("case: BUTTON_WEST_STATE_PRESSED");
      if (buttonHardwareUp(3)) {
        buttonStateWest = BUTTON_WEST_STATE_CHECK_RELEASED;
      }
      break;
    case BUTTON_WEST_STATE_CHECK_RELEASED:
      if (buttonHardwareDown(3)) {
        buttonStateWest = BUTTON_WEST_STATE_PRESSED;
      }
      else if ((buttonHardwareUp(3)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        buttonStateWest = BUTTON_WEST_STATE_RELEASED;
      }
      break;
  }
}

void buttonNoordPressedEntry() {
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
void buttonZuidPressedEntry() {
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

void buttonOostPressedEntry() {
  // zet hier de status van de licht knoppen in een tijderelijke array *kan niet met een for loop ivm met andere lengthe van de arrays*
  buttonsPressedTemp[0] = buttonsPressed[0];
  buttonsPressedTemp[1] = buttonsPressed[2];
  //1. check of de trein vanaf west kwam
  if (buttonsPressed[3] == 1) {
    treinIsBezig = false;
    treinIsNetWeg = true;
    // De trein kwam vanuit west
    // nu kunnen we de lampen weer aan laten gaan.
    // 1 krijg lampen van de array
    // 2 zet lampen aan
    // 3 reset de oost knop
    Serial.println("De trein kwam vanaf west");
    // reset de west knop
    //    buttonsPressed[3] = 0;
    if (buttonsPressedTemp[0] == 1) {
      buttonNoordPressedEntry();
    } else if (buttonsPressedTemp[2] == 1) {
      buttonZuidPressedEntry();
    }
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
    else if (timerButtonZuidPressedEntryCurrentLightGreen){
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

void buttonWestPressedEntry() {
  // zet hier de status van de licht knoppen in een tijderelijke array *kan niet met een for loop ivm met andere lengthe van de arrays*
  buttonsPressedTemp[0] = buttonsPressed[0];
  buttonsPressedTemp[1] = buttonsPressed[2];
  //1. check of de trein vanaf oost kwam
  if (buttonsPressed[1] == 1) {
    treinIsBezig = false;
    treinIsNetWeg = true;
    // reset de oost knop
    //    buttonsPressed[1] = 0;
    Serial.println("De trein kwam vanaf oost");
    // De trein kwam vanuit oost
    // Doe hier de logica van het opheffen van de trein.
    // als noord had gedrukt mag noord eerst.
    if (buttonsPressedTemp[0] == 1) {
      buttonNoordPressedEntry();
    } else if (buttonsPressedTemp[2] == 1) {
      buttonZuidPressedEntry();
    }
  } else {
    treinIsBezig = true;
    Serial.println("De trein kwam vanuit west");
    // De trein kwam vauit west
    // zet de lamp noord direct op geel en rood.
    if (timerButtonNoordPressedEntryCurrentLightGreen) {
      timerButtonNoordPressedEnteryCurrent = millis();
      timerButtonNoordPressedEntryIsBezig = true;
      ledControlSetLedOff(leds[1], leds[3]);
      ledControlSetLedOn(leds[2], leds[2]);
    }
    else if (timerButtonZuidPressedEntryCurrentLightGreen){
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

//
//void buttonReleasedEntry(int buttonNumber) {
//  // <nothing>
//}
//void buttonReleasedDo(int buttonNumber) {
//  // <nothing>
//}
//void buttonReleasedExit(int buttonNumber) {
//  // <nothing>
//}


void buttonCheckPressedEntry(int buttonNumber) {
  buttonPrevious = millis();
}
//void buttonCheckPressedDo(int buttonNumber) {
//  // <nothing>
//}
//void buttonCheckPressedExit(int buttonNumber) {
//  // <nothing>
//}

//
//void buttonPressedEntry(int buttonNumber) {
//  // <nothing>
//}
//void buttonPressedDo(int buttonNumber) {
//  // <nothing>
//}
//void buttonPressedExit(int buttonNumber) {
//  // <nothing>
//}


void buttonCheckReleasedEntry() {
  buttonPrevious = millis();
}
//void buttonCheckReleasedDo(int buttonNumber) {
//  // <nothing>
//}
//void buttonCheckReleasedExit(int buttonNumber) {
//  // <nothing>
//}
