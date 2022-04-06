String previousOvergangState;

// variable word gebruikt om Serial prints te laten zien in de console.
const boolean DEBUG_MODE = false;


void setup() {
  Serial.begin(115200);
  Serial.println(" \n ------------ \n System ready \n ------------ \n");
  if(DEBUG_MODE){Serial.println("\n \n Debug is set to 'true' \n");}
  
  if(DEBUG_MODE){Serial.println("Leds setup...");}
  ledControllSetup();
  if(DEBUG_MODE){Serial.println("Buttons setup...");}
  buttonHardwareSetup();
  buttonControllSetup();
  if(DEBUG_MODE){Serial.println("Buzzer setup...");}
  buzzerControllSetup();
  if(DEBUG_MODE){Serial.println("Servo setup...");}
  servoControllSetup();
  if(DEBUG_MODE){Serial.println("Shiftregister setup...");}
  registerControllSetup();
}

void loop() {
  overgangStateMachineLoop();
  buttonLoop();
  if(Serial.available()){
    if(Serial.read() == 'r'){
      setResetServoAantalKeerGeopent();
    }
  }
  if(DEBUG_MODE){delay(125);}
}
