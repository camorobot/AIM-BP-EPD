const int STARTUP = 0;
const int PASSIVE = 1;
const int VOERTUIG_PASSEREN = 2;
const int VOETGANGER_PASSEREN = 3;
const int ONTRUIMINGSTIJD = 4;
const int LICHTEN_OP_GROEN = 5;
const int LICHTEN_OP_GEEL = 6;
const int TREIN_PASSEREN = 7;
const int TREIN_VERTREKKEN = 8;


unsigned long ontruimingstijdPreviousMillis = 0;
boolean ontruimingstijdRunning = false;
const int ONTRUIMINGSTIJDDELAY = 2000;

const int LICHTENDELAY = 1500;
unsigned long lichtenPreviousMillis = 0;

boolean treinIsBezig = false;

String overgangDirection;

//String previousOvergangState;
int overgangState = 0;

void overgangStateMachineLoop(){
  switch(overgangState){
    case PASSIVE:
      if(getButtonPressed(0)){
        setOvergangDirection("noord");
        setOvergangState(VOERTUIG_PASSEREN);
        previousOvergangState = "PASSIVE";
        break;
      } else if(getButtonPressed(2)){
        setButtonPressed(2,0);
        setOvergangDirection("zuid");
        setOvergangState(VOERTUIG_PASSEREN);
        previousOvergangState = "PASSIVE";
        break;
      } else {
        previousOvergangState = "PASSIVE";
      }
      if(DEBUG_MODE){Serial.println(F("CASE: passive"));}
      break;
    case STARTUP:
      if(DEBUG_MODE){Serial.println(F("CASE: startup"));}
      startup_do();
      break;
    case VOERTUIG_PASSEREN:
      if(DEBUG_MODE){Serial.println(F("CASE: voertuigen_passeren"));}
      if(!ontruimingstijdRunning){
        if(DEBUG_MODE){Serial.println(F("VOERTUIG_PASSEREN: - Ontruimingstijd is niet bezig"));}
        if(previousOvergangState == "VOERTUIG_PASSEREN"){
          if(DEBUG_MODE){Serial.println(F("VOERTUIG_PASSEREN: - entry"));}
          voertuigPasseren_entry();
          break;
        }
        if(DEBUG_MODE){Serial.println(F("VOERTUIG_PASSEREN: - do"));}
        voertuigPasseren_do(); 
      }
      break;
    case VOETGANGER_PASSEREN:
      if(DEBUG_MODE){Serial.println(F("CASE: voetganger_passeren"));}
      if(!ontruimingstijdRunning){
      }
      break;
    case ONTRUIMINGSTIJD:
      if(DEBUG_MODE){Serial.println(F("CASE: ontruimingstijd"));}
      if(previousOvergangState != "ONTRUIMINGSTIJD"){
          if(DEBUG_MODE){Serial.println(F("CASE: ontruimingstijd: - entry"));}
          ontruimingstijd_entry();
          break;
        } else {
          if(DEBUG_MODE){Serial.println(F("CASE: ontruimingstijd: - do"));}
          ontruimingstijd_do();
          break;
        }
      break;
    case LICHTEN_OP_GROEN:
      if(DEBUG_MODE){Serial.println(F("CASE: lichten_op_groen"));}
      if(!ontruimingstijdRunning){
        if(previousOvergangState != "LICHTEN_OP_GROEN"){
          if(DEBUG_MODE){Serial.println(F("CASE: lichten_op_groen: - entry"));}
          lichtenOpGroen_entry();
          break;
        } else {
          if(DEBUG_MODE){Serial.println(F("CASE: lichten_op_groen: - do"));}
          lichtenOpGroen_do();
          break;
        }
      }
    case LICHTEN_OP_GEEL:
      if(DEBUG_MODE){Serial.println(F("CASE: lichten_op_geel"));}
      if(!ontruimingstijdRunning){
        if(previousOvergangState != "LICHTEN_OP_GEEL"){
          if(DEBUG_MODE){Serial.println(F("CASE: lichten_op_geel: - entry"));}
          lichtenOpGeel_entry();
          break;
        } else {
          if(DEBUG_MODE){Serial.println(F("CASE: lichten_op_geel: - do"));}
          lichtenOpGeel_do();
          break;
        }
      }
    case TREIN_PASSEREN:
      if(DEBUG_MODE){Serial.print("previousOvergangState: = ");}
      if(DEBUG_MODE){Serial.println(previousOvergangState);}
      if(DEBUG_MODE){Serial.println(F("CASE: trein_passeren"));}
      if(previousOvergangState != "TREIN_PASSEREN"){
        if(DEBUG_MODE){Serial.println(F("CASE: trein_passeren: - entry"));}
        treinPasseren_entry();
        break;
      } else {
        if(DEBUG_MODE){Serial.println(F("CASE: trein_passeren: - do"));}
        treinPasseren_do();
        break;
      }
    case TREIN_VERTREKKEN:
      if(previousOvergangState != "TREIN_VERTREKKEN"){
        if(DEBUG_MODE){Serial.println(F("CASE: trein_vertrekken: - entry"));}
        treinVertrekken_entry();
        break;
      } else {
        if(DEBUG_MODE){Serial.println(F("CASE: trein_vertrekken: - do"));}
        treinVertrekken_do();
      }
      break;
  }
}

void startup_do(){
  // Bij het opstarten moet het volgende gebeuren.
  // De lampen van noord en zuid moeten allebij op rood.
  // De display moet het getal 0 aangeven.
  ledControlSetLedOn(leds[0],leds[3]);
  sevenSegBlank();
  sevenSegWrite(1);
  overgangState = PASSIVE;
}

void voertuigPasseren_entry(){
  // 1 bekijk of voertuig van noord of zuid komt.
  // 2 bekijk of de andere kant niet al groen heeft.
  // 2.1 Als de andere kant groen heeft. onthoud dat
  // deze kant moet overteken + Ontruimingstijd (2 sec).
  if(getButtonPressed(0) == 1){ // knop noord is ingedrukt.
    if(DEBUG_MODE){Serial.println(F("voertuigen_passeren: - Knop noord is gedrukt."));}
    if(getButtonPressed(2) != 1){ // de knop van zuid is NIET gedrukt dus die heeft op dit moment GEEN groen.
      
    } else { // zuid heeft op dit moment groen, dus na de ontruimingstijd kan noord.
      
    }
  } else if(getButtonPressed(2) == 1){ // knop zuid is ingedrukt.
    if(DEBUG_MODE){Serial.println(F("voertuigen_passeren: - Knop zuid is gedrukt."));}
  }
}

void lichtenOpGroen_entry(){
  // 1. start lichten timer
  // 2. verander naar do
  // 3. zet lichten
  previousOvergangState = "LICHTEN_OP_GROEN";
  lichtenPreviousMillis = millis();
  if(overgangDirection == "noord"){
    if(DEBUG_MODE){Serial.println(F("lichten_op_groen: - Knop noord is gedrukt."));}
    ledControlSetLedOff(6,6);
    ledControlSetLedOn(4,4);
  } else if(overgangDirection == "zuid"){
    if(DEBUG_MODE){Serial.println(F("lichten_op_groen: - Knop zuid is gedrukt."));}
    ledControlSetLedOff(10,10);
    ledControlSetLedOn(7,7);
  }
}

void lichtenOpGroen_do(){
  // wacht op lichten timer
  // als timer voorbij is zet lichten op geel.
  if(millis() - lichtenPreviousMillis >= LICHTENDELAY){
    if(DEBUG_MODE){Serial.println(F("Timer is voorbij -> lampen naar geel"));}
    overgangState = LICHTEN_OP_GEEL;
  }
}

void lichtenOpGeel_entry(){
  // 1. start lichten timer
  // 2. verander naar do
  // 3. zet lichten
  previousOvergangState = "LICHTEN_OP_GEEL";
  lichtenPreviousMillis = millis();
  if(overgangDirection == "noord"){
    if(DEBUG_MODE){Serial.println(F("lichten_op_geel: - Knop noord is gedrukt."));}
    ledControlSetLedOff(4,4);
    ledControlSetLedOn(5,5);
  } else if(overgangDirection == "zuid"){
    if(DEBUG_MODE){Serial.println(F("lichten_op_geel: - Knop zuid is gedrukt."));}
    ledControlSetLedOff(7,7);
    ledControlSetLedOn(8,8);
  }
}

void lichtenOpGeel_do(){
  // wacht op lichten timer
  // als timer voorbij is zet lichten op geel.
  if(millis() - lichtenPreviousMillis >= LICHTENDELAY){
    if(DEBUG_MODE){Serial.println(F("lichten_op_geel_do: - voordat we kijen waar het verkeer vandaan komt."));}
    if(overgangDirection == "noord"){
      if(DEBUG_MODE){Serial.println(F("lichten_op_geel_do: - verkeer komt vanaf noord"));}
      ledControlSetLedOff(5,5);
      ledControlSetLedOn(6,6);
      setButtonPressed(0,0);
    } else if(overgangDirection == "zuid"){
      if(DEBUG_MODE){Serial.println(F("lichten_op_geel_do: - verkeer komt vanaf zuid"));}
      ledControlSetLedOff(8,8);
      ledControlSetLedOn(10,10);
      setButtonPressed(2,0);
    }
    overgangDirection = "";
    // start de onruimigstijd.
    if(DEBUG_MODE){Serial.println(F("lichten_op_geel_do: - keuze voor dat trein."));}
    if(treinIsBezig){
      if(DEBUG_MODE){Serial.println(F("lichten_op_geel_do: - keuze trein is actief"));}
      previousOvergangState = "TREIN_PASSEREN";
      overgangState = TREIN_PASSEREN;
    } else{
      overgangState = ONTRUIMINGSTIJD;
    }
  }
}

void treinPasseren_entry(){
  previousOvergangState = "TREIN_PASSEREN";
  treinIsBezig = true;
  if(DEBUG_MODE){Serial.print("previousOvergangState: = ");}
  if(DEBUG_MODE){Serial.println(previousOvergangState);}
  if((getLedStatus(1) == 1) || (getLedStatus(2) == 1)){
    if(DEBUG_MODE){Serial.println(F("trein_passeren_entry: - Er is verkeer uit het noorden"));}
    overgangDirection = "noord";
    overgangState = LICHTEN_OP_GEEL;
  } else if ((getLedStatus(4) == 1) || (getLedStatus(5) == 1)){
    if(DEBUG_MODE){Serial.println(F("trein_passeren_entry: - Er is verkeer uit het zuiden"));}
    overgangDirection = "zuid";
    overgangState = LICHTEN_OP_GEEL;
  } else {
    if(DEBUG_MODE){Serial.println(F("trein_passeren_entry: - Er is geen verkeer momenteel."));}
    previousOvergangState = "TREIN_PASSEREN";
  }
}

void treinPasseren_do(){
  // 1 klink buzzer
  // 2 knipper lampen
  // 3 sluit slagboom
  ledControlLedsBlink(5,8);
  if((getServoCurrentPos() != 88)){
    if(DEBUG_MODE){Serial.print(F("Huidige stand van slagboom is "));}
    if(DEBUG_MODE){Serial.print(getServoCurrentPos());}
    if(DEBUG_MODE){Serial.println(F(" graden."));}
    buzzerBeep();
    moveServo(89);
  } else {
    buzzerStop();
  }
}

void treinVertrekken_entry(){
  previousOvergangState = "TREIN_VERTREKKEN";
}

void treinVertrekken_do(){
  ledControlLedsBlink(5,8);
  if((getServoCurrentPos() != 0)){
    if(DEBUG_MODE){Serial.print(F("Huidige stand van slagboom is "));}
    if(DEBUG_MODE){Serial.print(getServoCurrentPos());}
    if(DEBUG_MODE){Serial.println(F(" graden."));}
    buzzerBeep();
    moveServo(0);
  } else {
    if(!displayTimerIsDone){
      buzzerStop();
      buzzerBeep3();
      countdownDisplayFrom5To0();
      if(DEBUG_MODE){Serial.println(F("rein_vertrekken_do: - countdown display."));}
    } else {
      if(DEBUG_MODE){Serial.println(F("trein_vertrekken_do: - Slagboom is beneden."));}
      buzzerStop();
      setButtonPressed(1,0);
      setButtonPressed(3,0);
      ledControlSetLedOff(5,8);
      treinIsBezig = false;
      displayTimerIsDone = false;
      previousOvergangState = "PASSIVE";
      setServoAantalKeerGeopent();
      setOvergangState(PASSIVE);
      Serial.print("Slagboom is ");
      Serial.print(getServoAantalKeerGeopent());
      Serial.println(" keer geopent.");
    }
  }
}

void ontruimingstijd_entry(){
  ontruimingstijdPreviousMillis = millis();
  previousOvergangState = "ONTRUIMINGSTIJD"; 
}

void voertuigPasseren_do(){
  overgangState = LICHTEN_OP_GROEN;
}

void ontruimingstijd_do(){
  ontruimingstijdRunning = true;
  if ((millis() - ontruimingstijdPreviousMillis) >= ONTRUIMINGSTIJDDELAY) {
    // de ontruimingstijd is afgelopen en de state kan dus weer naar PASSIVE;
    ontruimingstijdRunning = false;
    overgangState = PASSIVE;
  } 
}

void setOvergangState(int state){
  overgangState = state;
}

void setOvergangDirection(String incommingDirection){
  overgangDirection = incommingDirection;
}
