// vars 
const int BUZZER = A1;
const int BUZZER_LOW_FREQUENCY = 5;
const int BUZZER_HIGH_FREQUENCY = 50;
const int BUZZER_TRIPLE_PULSE_INTERVAL = 355;
const int BUZZER_TRIPLE_PULSE_FREQUENCY = 6 / (BUZZER_TRIPLE_PULSE_INTERVAL / 2000.f);
const int BUZZER_OFF_FREQUENCY = 0;

unsigned long buzzerPreviousMillis = 0;
int buzzerFrequency = BUZZER_LOW_FREQUENCY;

// Methods
void setBuzzerFrequency( int frequency) {
  buzzerFrequency = frequency;
}

void buzzerSetup() {
  pinMode(BUZZER, OUTPUT);
}

void buzzerBuzz() {
  unsigned long currentMillis = millis();
  if (buzzerFrequency != BUZZER_OFF_FREQUENCY) {
    long buzzerDelayVal = 10000 / buzzerFrequency / 2; // 1 seconde gedeeld door freq gedeeld door het aantal states (aan/uit)
    if (currentMillis - buzzerPreviousMillis >= buzzerDelayVal) {
      digitalWrite(BUZZER, HIGH);
      buzzerPreviousMillis = currentMillis;
    }
    else
      digitalWrite(BUZZER, LOW);
  }
}

// tripple pulse states
const int STATE_BUZZER_TRIPLE_PULSE_ON = 0;
const int STATE_BUZZER_TRIPLE_PULSE_OFF = 1;
int current_state_buzzerTriplePulse;
unsigned long triplePulseTimer = 0;

void buzzerTriplePulseSetup() {
  current_state_buzzerTriplePulse = STATE_BUZZER_TRIPLE_PULSE_ON;
  state_buzzer_triple_pulse_on_Entry();
}

void buzzerTriplePulse() {
  unsigned long currentMillis = millis();
  switch (current_state_buzzerTriplePulse)
  {
    case STATE_BUZZER_TRIPLE_PULSE_ON:
      if (currentMillis - triplePulseTimer >= BUZZER_TRIPLE_PULSE_INTERVAL)
      {
        current_state_buzzerTriplePulse = STATE_BUZZER_TRIPLE_PULSE_OFF;
        state_buzzer_triple_pulse_off_Entry();
      }
      break;
    case STATE_BUZZER_TRIPLE_PULSE_OFF:
      if (currentMillis - triplePulseTimer >= BUZZER_TRIPLE_PULSE_INTERVAL)
      {
        current_state_buzzerTriplePulse = STATE_BUZZER_TRIPLE_PULSE_ON;
        state_buzzer_triple_pulse_on_Entry();
      }
      break;
  }
}

void state_buzzer_triple_pulse_on_Entry() {
  triplePulseTimer = millis();
  setBuzzerFrequency(BUZZER_TRIPLE_PULSE_FREQUENCY);
}

void state_buzzer_triple_pulse_off_Entry() {
  triplePulseTimer = millis();
  setBuzzerFrequency(BUZZER_OFF_FREQUENCY);
}

// getters
int getBuzzerLowFrequency() {
  return BUZZER_LOW_FREQUENCY;
}
int getBuzzerHighFrequency() {
  return BUZZER_HIGH_FREQUENCY;
}
int getBuzzerOffFrequency() {
  return BUZZER_OFF_FREQUENCY;
}