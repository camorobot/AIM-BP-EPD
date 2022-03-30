
const int latchpin = 11;
const int datapin = 12;
const int clockpin = 9;

void registerSetup() {
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
  sevenSegBlank();
}

void sevenSegWrite(int number) {
  digitalWrite(latchpin, LOW);
  shiftOut(datapin, clockpin, MSBFIRST, registerDisplay[number]);
  digitalWrite(latchpin, HIGH);
}

void sevenSegBlank() {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchpin, LOW);
  shiftOut(datapin, clockpin, MSBFIRST, B00000000);
  // set the latchPin to high potential, after sending data
  digitalWrite(latchpin, HIGH);
}
