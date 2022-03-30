// vars die hier staan kreeg ik op geen enlkele mogelijkheid in het eigen "hardware tabje".

// word gebruikt om te kijken of er op een knop is gedrukt.
// zoja dan word de 0 naar een 1 veranderd.
int buttonsPressed[] = {0,0,0,0};
int buttonsPressedTemp[] = {0,0};


#include <Servo.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Serial setup.. Done");
  Serial.println("Sero Setup...");
  servoSetup();
  Serial.println("Led setup...");
  ledSetup();
  Serial.println("Buttonhardware Setup...");
  buttonHardwareSetup();
  Serial.println("Button software Setup...");
  buttonSetup();
  Serial.println("Shiftregister etup...");
  registerSetup();
  Serial.println("Buzzer Setup...");
  buzzerSetup();
  Serial.println("Timers Setup...");
  timerSetup();
//  Serial.println("overgangStateMachine");
//  overgangStateSetup();
}

void loop() {
  timerLoop();
  buttonLoop();
  countdownDisplayFrom5To0Loop();
  if(buttonsPressed[0] == 1 || buttonsPressed[2] == 1){
    Serial.println("FAKKA KNOP NOORD OF ZUID IS AAN");
  }
  Serial.println(buttonsPressed[0]);
  Serial.println(buttonsPressed[1]);
  Serial.println(buttonsPressed[2]);
  Serial.println(buttonsPressed[3]);
  Serial.println("Original /\ ||| temp \/");
  Serial.println(buttonsPressedTemp[0]);
  Serial.println(buttonsPressedTemp[1]);
  // DEZE DELAY HEEFT NIKS TE MAKEN MET HET PROGRAMMA ZELF EN IS PUUR VOOR HET DEBUGGEN
  // ::REMINDER - WEGHALEN::
  delay(100);
}
