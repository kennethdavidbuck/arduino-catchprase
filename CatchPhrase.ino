
#include "GameView.h"

const int TEAM_ONE_BUTTON_PIN = 2;
const int TEAM_TWO_BUTTON_PIN = 3;

const unsigned long DEBOUNCE_TIME = 150000;

volatile int teamOneScore = 0;
volatile int teamTwoScore = 0;

volatile unsigned long lastMicros = 0;

GameView *view;

void initializeInterrupt(int pin);
bool buttonIsPressed(int pin);
void handler();
void debounceHandler();

/**
 * 
 */
void initializeInterrupt(int pin) {
  attachInterrupt(digitalPinToInterrupt(pin), debounceHandler, FALLING);
  pinMode(pin, INPUT_PULLUP);
}

/**
 * 
 */
void debounceHandler() {
  unsigned long currentMicros = (long) micros();
  
  if(currentMicros - lastMicros >= DEBOUNCE_TIME) {
    handler();
    lastMicros = currentMicros;
  }  
}

/**
 * 
 */
void handler() {
  if(buttonIsPressed(TEAM_ONE_BUTTON_PIN)) {
    teamOneScore++;
  } else if(buttonIsPressed(TEAM_TWO_BUTTON_PIN)) {
    teamTwoScore++;
  }  
}

/**
 * 
 */
bool buttonIsPressed(int pin) {
  return digitalRead(pin) == LOW;
}

void setup() {
  initializeInterrupt(TEAM_ONE_BUTTON_PIN);
  initializeInterrupt(TEAM_TWO_BUTTON_PIN);

  view = new GameView();  
}

void loop() {
  view->setTeamScores(teamOneScore, teamTwoScore);
}

