
#include "CatchPhrase.h"
#include "GameView.h"

// Pins
const int TEAM_ONE_PIN    = 2;
const int TEAM_TWO_PIN    = 3;
const int CATEGORY_PIN    = 4;
const int STOP_START_PIN  = 5;

// Scores
int teamOneScore = 0;
int teamTwoScore = 0;

// Events
volatile int teamOneScoreEvent = false;
volatile int teamTwoScoreEvent = false;

// Debounce Values
volatile unsigned long lastMicros = 0;
const unsigned long DEBOUNCE_TIME = 100000;

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
  teamOneScoreEvent = digitalRead(TEAM_ONE_PIN) == LOW;
  teamTwoScoreEvent = digitalRead(TEAM_TWO_PIN) == LOW;
}

void loop() {
  
  if(teamOneScoreEvent) {
    teamOneScore++;
    teamOneScoreEvent = false;
  }

  if(teamTwoScoreEvent) {
    teamTwoScore++;
    teamTwoScoreEvent = false;
  }
    
  view->setTeamScores(teamOneScore, teamTwoScore);
}
