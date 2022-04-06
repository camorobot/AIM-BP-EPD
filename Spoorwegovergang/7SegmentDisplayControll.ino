const int DISPLAY_TIMER = 1000;
unsigned long displayPrevious = millis();
//unsigned long displayCurrentTime = millis();
boolean displayTimerIsDone = false;
boolean displayTimerIsRunningDone = false;
int currentDisplayLoopNumber = 7;
//
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
//
void countdownDisplayFrom5To0() {
  // als deze functie moet blijven worden geroepen om te zorgen dat het netjes afteld van 5 naar 0;
  if ((millis() - displayPrevious) >= DISPLAY_TIMER) {
    displayPrevious = millis();
    if(currentDisplayLoopNumber <= 0){
      displayTimerIsDone = true;
      currentDisplayLoopNumber = 7;
    } else{ 
      displayTimerIsDone = false;
      sevenSegBlank();
      sevenSegWrite(currentDisplayLoopNumber);
      currentDisplayLoopNumber--;
    }
  }
}
//
void setDisplayTimerRunning(boolean state){
  displayTimerIsDone = state;
}
