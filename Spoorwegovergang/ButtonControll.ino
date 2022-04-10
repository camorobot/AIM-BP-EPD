//// Module Button
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

const int BUTTON_DUBBLE_PRESSED_INTERVAL = 3000;
const int BUTTON_INTERVAL = 10;
unsigned long buttonPrevious;
unsigned long buttonDubblePressedPrevious;

boolean buttonTimer = false;

// geld alleen voor noord en zuid.
int buttonsDubblePressed[] = {0, 0};

int buttonsPressed[] = {0, 0, 0, 0};

void buttonControllSetup() {
  buttonStateNoord = BUTTON_NOORD_STATE_RELEASED;
  buttonStateZuid = BUTTON_ZUID_STATE_RELEASED;
  buttonStateOost = BUTTON_OOST_STATE_RELEASED;
  buttonStateWest = BUTTON_WEST_STATE_RELEASED;
}


void buttonLoop() {
  switch (buttonStateNoord) {
    case BUTTON_NOORD_STATE_RELEASED:
      if (buttonHardwareDown(0)) {
        if(DEBUG_MODE){Serial.println("check: ButtonHardwareDown[0]");}
        buttonStateNoord = BUTTON_NOORD_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_NOORD_STATE_CHECK_PRESSED:
      if (buttonHardwareUp(0)) {
        if(DEBUG_MODE){Serial.println("Button false positive");}
        buttonStateNoord = BUTTON_NOORD_STATE_RELEASED;
      }
      else if ((buttonHardwareDown(0)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        if(DEBUG_MODE){Serial.println("Button daadwerkelijk ingedrukt");}
        buttonsPressed[0] = 1;
        if(previousOvergangState == "PASSIVE"){
          buttonStateNoord = BUTTON_NOORD_STATE_PRESSED;
          buttonsPressed[0] = 1;
          setOvergangDirection("noord");
          setOvergangState(2);
        } 
        
        // --------------
//        buttonsDubblePressed[0]++;
        // kijk of er 2 keer op de knop word gedrukt.
        // 1. start een timer van 1.5 seconden.
        // 2. if stakement als er weer een knop word gedrukt.
//        if(!buttonTimer){
//          buttonTimer = true;
//          buttonDubblePressedPrevious = millis();
//        }
//        if(!resetButtonTimer){
//          resetButtonTimer = true;
//          buttonDubblePressedPrevious = millis();
//        }
//        if(DEBUG_MODE){Serial.println("BUTTON_NOORD_STATE_CHECK_PRESSED: - net voor de timer.");}
//        Serial.println(buttonsDubblePressed[0]);
//        if (buttonsDubblePressed[0] == 2 && (millis() - buttonDubblePressedPrevious <= BUTTON_DUBBLE_PRESSED_INTERVAL)) {
//          if(DEBUG_MODE){Serial.println("BUTTON_NOORD_STATE_CHECK_PRESSED: - Er is dubbel gedrukt, dus het systeem weet dat er een voetganger is.");}
//          buttonsDubblePressed[0] = 0;
//          resetButtonTimer = false;
//          setOvergangState(3); // VOETGANGER_OVERSTEKEN
//        } else if ((millis() - buttonDubblePressedPrevious >= BUTTON_DUBBLE_PRESSED_INTERVAL)){
//          if(DEBUG_MODE){Serial.println("BUTTON_NOORD_STATE_CHECK_PRESSED: - Er is maar 1 keer gedrukt dus we kunnen over gaan naar de state van de voertuigen.");}
//          buttonsDubblePressed[0] = 0;
//          resetButtonTimer = false;
//        } 
        // --------------

        
        
        //        buttonNoordPressedEntry();
      }
      break;
    case BUTTON_NOORD_STATE_PRESSED:
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
      if (buttonHardwareDown(2)) {
        if(DEBUG_MODE){Serial.println("check: ButtonHardwareDown[2]");}
        buttonStateZuid = BUTTON_ZUID_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_ZUID_STATE_CHECK_PRESSED:
      if (buttonHardwareUp(2)) {
        if(DEBUG_MODE){Serial.println("Button false positive");}
        buttonStateZuid = BUTTON_ZUID_STATE_RELEASED;
      }
      else if ((buttonHardwareDown(2)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        if(DEBUG_MODE){Serial.println("Button daadwerkelijk ingedrukt");}
        buttonsPressed[2] = 1;
        if(previousOvergangState == "PASSIVE"){
          buttonStateZuid = BUTTON_ZUID_STATE_PRESSED;
          setOvergangDirection("zuid");
          setOvergangState(2);
        }
      }
      break;
    case BUTTON_ZUID_STATE_PRESSED:
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
      if (buttonHardwareDown(1)) {
        if(DEBUG_MODE){Serial.println("check: ButtonHardwareDown[1]");}
        buttonStateOost = BUTTON_OOST_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_OOST_STATE_CHECK_PRESSED:
      if (buttonHardwareUp(1)) {
        if(DEBUG_MODE){Serial.println("Button false positive");}
        buttonStateOost = BUTTON_OOST_STATE_RELEASED;
      }
      else if ((buttonHardwareDown(1)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        if(DEBUG_MODE){Serial.println("Button daadwerkelijk ingedrukt");}
        buttonStateOost = BUTTON_OOST_STATE_PRESSED;
        if(buttonsPressed[3] == 1){
          if(DEBUG_MODE){Serial.println(F("CASE: BUTTON_OOST_STATE_CHECK_PRESSED: - trein kwam vanaf west. dus we gaan de slagboom weer openen"));}
          buttonsPressed[1] = 1;
          setOvergangState(8);
        } else if(buttonsPressed[1] != 1){
          if(DEBUG_MODE){Serial.println(F("CASE: BUTTON_OOST_STATE_CHECK_PRESSED: - trein kwam vanaf oost. dus we gaan de slagboom sluiten"));}
          buttonsPressed[1] = 1;
          setOvergangState(7);
        }
      }
      break;
    case BUTTON_OOST_STATE_PRESSED:
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
      if (buttonHardwareDown(3)) {
        if(DEBUG_MODE){Serial.println("check: ButtonHardwareDown[3]");}
        buttonStateWest = BUTTON_WEST_STATE_CHECK_PRESSED;
      }
      break;
    case BUTTON_WEST_STATE_CHECK_PRESSED:
      if (buttonHardwareUp(3)) {
        if(DEBUG_MODE){Serial.println("Button false positive");}
        buttonStateWest = BUTTON_WEST_STATE_RELEASED;
      }
      else if ((buttonHardwareDown(3)) && (millis() - BUTTON_INTERVAL >= buttonPrevious)) {
        if(DEBUG_MODE){Serial.println("Button daadwerkelijk ingedrukt");}
        buttonStateWest = BUTTON_WEST_STATE_PRESSED;
        if(buttonsPressed[1] == 1){
          if(DEBUG_MODE){Serial.println(F("CASE: BUTTON_OOST_STATE_CHECK_PRESSED: - trein kwam vanaf oost. dus we gaan de slagboom weer openen"));}
          buttonsPressed[3] = 1;
          setOvergangState(8);
        } else if(buttonsPressed[3] != 1){
          if(DEBUG_MODE){Serial.println(F("CASE: BUTTON_OOST_STATE_CHECK_PRESSED: - trein kwam vanaf west. dus we gaan de slagboom sluiten"));}
          buttonsPressed[3] = 1;
          setOvergangState(7);
        }
        //        buttonWestPressedEntry();
      }
      break;
    case BUTTON_WEST_STATE_PRESSED:
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
//
//
//void buttonReleasedEntry(int buttonNumber) {
// <nothing>
//}
//void buttonReleasedDo(int buttonNumber) {
// <nothing>
//}
//void buttonReleasedExit(int buttonNumber) {
// <nothing>
//}
//
//
//void buttonCheckPressedEntry(int buttonNumber) {
//  buttonPrevious = millis();
//}
//void buttonCheckPressedDo(int buttonNumber) {
// <nothing>
//}
//void buttonCheckPressedExit(int buttonNumber) {
// <nothing>
//}
//
//
//void buttonPressedEntry(int buttonNumber) {
// <nothing>
//}
//void buttonPressedDo(int buttonNumber) {
// <nothing>
//}
//void buttonPressedExit(int buttonNumber) {
// <nothing>
//}
//
//
//void buttonCheckReleasedEntry() {
//  buttonPrevious = millis();
//}
//void buttonCheckReleasedDo(int buttonNumber) {
// <nothing>
//}
//void buttonCheckReleasedExit(int buttonNumber) {
// <nothing>
//}
//
//void setButtonsPressed(int buttonInArray, boolean state) {
//  buttonsPressed[buttonInArray] = state;
//}

// getters and setters

int getButtonPressed(int buttonNumber) {
  return buttonsPressed[buttonNumber];
}

void setButtonPressed(int buttonNumber, int state){
  buttonsPressed[buttonNumber] = state;
}
