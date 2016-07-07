
#include "CatchPhrase.h"
#include "GameView.h"

// Messages
const String EMPTY        = "";
const String TEAM_ONE_WIN = " TEAM ONE WINS! ";
const String TEAM_TWO_WIN = " TEAM TWO WINS! ";

String currentMessage;

// 
const int POINTS_WIN = 7;

// Pins
const int TEAM_ONE_PIN    = 2;
const int TEAM_TWO_PIN    = 3;
const int CATEGORY_PIN    = 4;
const int STOP_START_PIN  = 5;

// Scores
int teamOneScore = 0;
int teamTwoScore = 0;

// Events
volatile int teamOneScoreEvent = 0;
volatile int teamTwoScoreEvent = 0;
volatile int nextCategoryEvent = 0;
volatile int stopStartEvent = 0;

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
  initializeInterrupt(TEAM_ONE_PIN, LOW);
  initializeInterrupt(TEAM_TWO_PIN, LOW);

  view = new GameView();

  currentMessage = EMPTY;
  
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

  switch(currentState) {
    case GAME_OVER:
      if(nextCategoryEvent) {
        currentState = STOPPED;
        nextCategoryEvent = 0;
      } else if(stopStartEvent) {
        currentState = STOPPED;
        stopStartEvent = 0;
      }
    
      break;
    case STOPPED:
      if(teamOneScoreEvent) {
        teamOneScore++;
        teamOneScoreEvent = 0;
      } else if(teamTwoScoreEvent) {
        teamTwoScore++;
        teamTwoScoreEvent = 0;
      }

      if(teamOneScore == POINTS_WIN || teamTwoScore == POINTS_WIN) {
        currentMessage = teamOneScore == POINTS_WIN ? TEAM_ONE_WIN : TEAM_TWO_WIN;

        currentState = GAME_OVER;
      }
      
      break;
    case STARTED:
      // timer runs
      // can switch phrases
      // can switch categories
      break;
  } 

  view->setPhrase(currentMessage);
  view->setTeamScores(teamOneScore, teamTwoScore);
}
