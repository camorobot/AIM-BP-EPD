
int buttons[] = {A3, A5, A4, A2};
const int AANTAL_BUTTONS = 4;

void buttonHardwareSetup() {
  for (int button = 0; button < AANTAL_BUTTONS; button++) {
    pinMode(buttons[button], INPUT);
  }
}

boolean buttonHardwareDown(int buttonNumber) {
  // Pull down resistor used.
  return (digitalRead(buttons[buttonNumber]) == HIGH);
  // if pull down resistor is used, compare to HIGH
}

boolean buttonHardwareUp(int buttonNumber) {
  return !buttonHardwareDown(buttonNumber);
}
