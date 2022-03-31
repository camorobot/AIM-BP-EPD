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

const int RESET_COMPLETE = 99;
int overgangState;

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

void buttonAndStateLoop() {
  switch (buttonStateNoord) {
    case BUTTON_NOORD_STATE_RELEASED:
//      Serial.println("case: BUTTON_NOORD_STATE_RELEASED");
      if (buttonHardwareDown(0)) {
        Serial.println("check: ButtonHardwareDown[0]");
        buttonStateNoord = BUTTON_NOORD_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_NOORD_STATE_CHECK_PRESSED:
//      Serial.println("case: BUTTON_NOORD_STATE_CHECK_PRESSED");
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
//      Serial.println("case: BUTTON_NOORD_STATE_PRESSED");
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
//      Serial.println("case: BUTTON_ZUID_STATE_RELEASED");
      if (buttonHardwareDown(2)) {
        Serial.println("check: ButtonHardwareDown[2]");
        buttonStateZuid = BUTTON_ZUID_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_ZUID_STATE_CHECK_PRESSED:
//      Serial.println("case: BUTTON_ZUID_STATE_CHECK_PRESSED");
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
//      Serial.println("case: BUTTON_ZUID_STATE_PRESSED");
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
//      Serial.println("case: BUTTON_OOST_STATE_RELEASED");
      if (buttonHardwareDown(1)) {
        Serial.println("check: ButtonHardwareDown[1]");
        buttonStateOost = BUTTON_OOST_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_OOST_STATE_CHECK_PRESSED:
//      Serial.println("case: BUTTON_OOST_STATE_CHECK_PRESSED");
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
//      Serial.println("case: BUTTON_OOST_STATE_PRESSED");
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
//      Serial.println("case: BUTTON_WEST_STATE_RELEASED");
      if (buttonHardwareDown(3)) {
        Serial.println("check: ButtonHardwareDown[3]");
        buttonStateWest = BUTTON_WEST_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_WEST_STATE_CHECK_PRESSED:
//      Serial.println("case: BUTTON_WEST_STATE_CHECK_PRESSED");
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
//      Serial.println("case: BUTTON_WEST_STATE_PRESSED");
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
  switch (overgangState) {
    // [case RESET_COMPLETE] reset allewaarden weer naar het begin.
    case RESET_COMPLETE:
      resetCompleteEntry();
  }
}

void buttonNoordPressedEntry() {
  buttonNoordLogic();
}
void buttonZuidPressedEntry() {
  buttonZuidLogic();
}

void buttonOostPressedEntry() {
  buttonOostLogic();
}

void buttonWestPressedEntry() {
  buttonWestLogic();
}

void buttonNoordPressedDo() {
//  Mag leeg zijn
}
void buttonZuidPressedDo() {
//  Mag leeg zijn
}

void buttonOostPressedDo() {
//  Mag leeg zijn
}

void buttonWestPressedDo() {
//  Mag leeg zijn
}

void buttonNoordPressedExit() {
//  Mag leeg zijn
}
void buttonZuidPressedExit() {
//  Mag leeg zijn
}

void buttonOostPressedExit() {
//  Mag leeg zijn
}

void buttonWestPressedExit() {
//  Mag leeg zijn
}


void buttonReleasedEntry(int buttonNumber) {
 <nothing>
}
void buttonReleasedDo(int buttonNumber) {
 <nothing>
}
void buttonReleasedExit(int buttonNumber) {
 <nothing>
}


void buttonCheckPressedEntry(int buttonNumber) {
  buttonPrevious = millis();
}
void buttonCheckPressedDo(int buttonNumber) {
 <nothing>
}
void buttonCheckPressedExit(int buttonNumber) {
 <nothing>
}


void buttonPressedEntry(int buttonNumber) {
 <nothing>
}
void buttonPressedDo(int buttonNumber) {
 <nothing>
}
void buttonPressedExit(int buttonNumber) {
 <nothing>
}


void buttonCheckReleasedEntry() {
  buttonPrevious = millis();
}
void buttonCheckReleasedDo(int buttonNumber) {
 <nothing>
}
void buttonCheckReleasedExit(int buttonNumber) {
 <nothing>
}

void setButtonsPressed(int buttonInArray, boolean state) {
  buttonsPressed[buttonInArray] = state;
}
