
#include "CatchPhrase.h"
#include "GameView.h"

// Pins
const int TEAM_ONE_PIN    = 2;
const int TEAM_TWO_PIN    = 3;
const int CATEGORY_PIN    = 4;
const int STOP_START_PIN  = 5;

// Scores
volatile int teamOneScore = 0;
volatile int teamTwoScore = 0;

// Debounce Values
volatile unsigned long lastMicros = 0;
const unsigned long DEBOUNCE_TIME = 150000;

// Views
GameView *view;

void setup() {
  initializeInterrupt(TEAM_ONE_PIN, LOW);
  initializeInterrupt(TEAM_TWO_PIN, LOW);

  view = new GameView();  
  
  view->setTeamScores(teamOneScore, teamTwoScore);
}

void initializeInterrupt(int pin, int state) {
  attachInterrupt(digitalPinToInterrupt(pin), debounceHandler, state);
  pinMode(pin, INPUT_PULLUP);
}

void debounceHandler() {
  unsigned long currentMicros = (long) micros();
  
  if(currentMicros - lastMicros >= DEBOUNCE_TIME) {
    handler();
    lastMicros = currentMicros;
  }  
}

void handler() {
  if(buttonIsPressed(TEAM_ONE_PIN)) {
    teamOneScore++;
  } else if(buttonIsPressed(TEAM_TWO_PIN)) {
    teamTwoScore++;
  }  
}

bool buttonIsPressed(int pin) {
  return digitalRead(pin) == LOW;
}

void loop() {
  view->setTeamScores(teamOneScore, teamTwoScore);
}
