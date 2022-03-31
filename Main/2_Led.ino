/*
    # LEDS
    Green North:        4
    Yellow North:       5
    Red North:          6
    
    Green South:        7
    Yellow South:       8
    Red South           10
 */

int leds[] = {10,4,5,6,7,8};
const int AANTAL_LEDS = 6;
const int AANTAL_ZELFDE_LEDS = 2;
boolean knipperenIsBezig = false;


void ledSetup() {
  for (int led = 0; led < AANTAL_LEDS; led++) {
    pinMode(leds[led], OUTPUT);
  }
//  zet de lichten op het begin gelijk op rood
  ledControlSetLedOn(leds[0], leds[3]);
}

//hiermee kan je 2leds tegelijk aanzetten
void ledControlSetLedOn (int led, int led2) {
  digitalWrite(led, HIGH);
  digitalWrite(led2, HIGH);
}

//hiermee kan je 2 leds tegelijk uitzetten
void ledControlSetLedOff (int led, int led2) {
  digitalWrite(led, LOW);
  digitalWrite(led2, LOW);
}

int getLedStatus(int ledNumberArray){
  return digitalRead(leds[ledNumberArray]);
}

// hiermee kunnen 2 leds tegelijk knipperen
int blinkSpeed = 500; 
unsigned long blinkPreviousMillis;
void ledControlLedsBlink (int led1, int led2) {
  if (knipperenIsBezig && (millis() - blinkPreviousMillis >= blinkSpeed)) {        
    blinkPreviousMillis = millis();                              
    digitalWrite(led1, !digitalRead(led1));
    digitalWrite(led2, !digitalRead(led2));                   
  }
}
