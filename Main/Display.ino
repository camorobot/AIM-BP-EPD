const int DISPLAY_TIMER = 1000;
unsigned long displayPrevious = millis();
//unsigned long displayCurrentTime = millis();
boolean displayTimerIsRunning = true;
int currentDisplayLoopNumber = 7;

int registerDisplay [7] {
  B00000000,  // -
  B01111011,  // 0
  B00001001,  // 1
  B10110011,  // 2
  B10011011,  // 3
  B11001001,  // 4
  B11011010,  // 5
  //  B11111010,  // 6
  //  B00001011,  // 7
  //  B11111011,  // 8
  //  B11011011   // 9
};

void countdownDisplayFrom5To0Loop() {
  // als deze functie moet blijven worden geroepen om te zorgen dat het netjes afteld van 5 naar 0;
  if (displayTimerIsRunning && ((millis() - displayPrevious) >= DISPLAY_TIMER)) {
    displayPrevious = millis(); // // prevent this code being run more then once
    Serial.println("Turned LED Off");
    if(currentDisplayLoopNumber <= 0){
      currentDisplayLoopNumber = 7;
      displayTimerIsRunning = false;
    } else{ 
      sevenSegBlank();
      sevenSegWrite(currentDisplayLoopNumber);
      currentDisplayLoopNumber--;
    }
  }
}

void setDisplayTimerRunning(boolean state){
  displayTimerIsRunning = state;
}
