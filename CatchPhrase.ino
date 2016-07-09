
#include "CatchPhrase.h"
#include "GameView.h"

// Messages
const String EMPTY        = "                ";
const String TEAM_ONE_WIN = " TEAM ONE WINS! ";
const String TEAM_TWO_WIN = " TEAM TWO WINS! ";
const String SUCCESS      = "    SUCCESS!    ";

String currentMessage;

// 
const int POINTS_WIN = 7;

// Pins
const int CATEGORY_PIN    = 0;
const int STOP_START_PIN  = 1;
const int TEAM_ONE_PIN    = 2;
const int TEAM_TWO_PIN    = 3;
const int NEXT_PIN        = 7;

// Scores
int teamOneScore = 0;
int teamTwoScore = 0;

// Events
volatile int teamOneScoreEvent = 0;
volatile int teamTwoScoreEvent = 0;
volatile int categoryEvent     = 0;
volatile int stopStartEvent    = 0;
volatile int nextEvent         = 0;

// States
typedef enum States {
  GAME_OVER,
  STOPPED,
  STARTED
};

int currentState = STOPPED;

// Debounce Values
volatile unsigned long lastMicros = 0;
const unsigned long DEBOUNCE_TIME = 100000;

// Views
GameView *view;

void setup() {
  initializeInterrupt(CATEGORY_PIN, LOW);
  initializeInterrupt(STOP_START_PIN, LOW);
  initializeInterrupt(TEAM_ONE_PIN, LOW);
  initializeInterrupt(TEAM_TWO_PIN, LOW);
  initializeInterrupt(NEXT_PIN, LOW);  

  view = new GameView();

  clearScores();
  currentMessage = EMPTY;
  
  view->setTeamScores(teamOneScore, teamTwoScore);
}

void clearEvents() {
  teamOneScoreEvent = 0;
  teamTwoScoreEvent = 0;
  categoryEvent     = 0;
  stopStartEvent    = 0;
  nextEvent         = 0;
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
  categoryEvent     = digitalRead(CATEGORY_PIN)   == LOW;
  stopStartEvent    = digitalRead(STOP_START_PIN) == LOW;
  teamOneScoreEvent = digitalRead(TEAM_ONE_PIN)   == LOW;
  teamTwoScoreEvent = digitalRead(TEAM_TWO_PIN)   == LOW;
  nextEvent         = digitalRead(NEXT_PIN)       == LOW;
}

void transitionToStarted() {
  clearEvents();
  currentState = STARTED;
}

void transitionToGameOver() {
  clearEvents();
  currentMessage = teamOneScore == POINTS_WIN ? TEAM_ONE_WIN : TEAM_TWO_WIN;
  currentState = GAME_OVER;
}

void transitionToStopped() {
  clearEvents();
  currentState = STOPPED;
}

void incrementTeamOneScore() {
  clearEvents();
  teamOneScore++;
}

void incrementTeamTwoScore() {
  clearEvents();
  teamTwoScore++;
}

void nextPhrase() {
  clearEvents();
}

bool gameIsWon() {
  clearEvents();
  
  if(teamOneScore == POINTS_WIN || teamTwoScore == POINTS_WIN) {
    return true;  
  }

  return false;
}

void clearScores() {
  clearEvents();
  teamOneScore = teamTwoScore = 0;
}

void loop() {

  switch(currentState) {
    case GAME_OVER:
      if(categoryEvent || stopStartEvent) {
        clearScores();
        transitionToStopped();
      }
  
      break;
    case STOPPED:
      if(teamOneScoreEvent) {
        incrementTeamOneScore();
      } else if(teamTwoScoreEvent) {
        incrementTeamTwoScore();
      } else if(stopStartEvent) {
        transitionToStarted();
      } else if(nextEvent) {
        nextPhrase();
      }

      if(gameIsWon()) {
        transitionToGameOver();
      }
      
      break;
    case STARTED:
      // timer runs
      // can switch phrases
      if(stopStartEvent) {
        transitionToStopped();
      } else if(nextEvent) {
        nextPhrase();
      }
   
      break;
  } 

  view->setPhrase(currentMessage);
  view->setTeamScores(teamOneScore, teamTwoScore);
}
