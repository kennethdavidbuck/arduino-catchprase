
#include "CatchPhrase.h"
#include "GameView.h"

const String EMPTY        = "                ";
const String TEAM_ONE_WIN = " TEAM ONE WINS! ";
const String TEAM_TWO_WIN = " TEAM TWO WINS! ";
const String SUCCESS      = "    SUCCESS!    ";

const int POINTS_WIN = 7;

volatile unsigned long lastMicros = 0;
const unsigned long DEBOUNCE_TIME = 100000;

typedef enum Pins {
  CATEGORY_PIN    = 0,
  STOP_START_PIN  = 1,
  TEAM_ONE_PIN    = 2,
  TEAM_TWO_PIN    = 3,
  NEXT_PIN        = 7
};

typedef enum States {
  GAME_OVER,
  STOPPED,
  STARTED
};

typedef enum Events {
  TEAM_ONE_SCORE_EVENT,
  TEAM_TWO_SCORE_EVENT,
  CATEGORY_EVENT,
  STOP_START_EVENT,
  NEXT_EVENT  
};

typedef struct Game {
  volatile int events[5]  = {0, 0, 0, 0, 0};
  String currentMessage   = EMPTY;
  int currentState        = STOPPED;
  int teamOneScore        = 0;
  int teamTwoScore        = 0;
  GameView *view          = new GameView();
};

// Create the game.
Game game;

void setup() {
  initializeInterrupt(CATEGORY_PIN, LOW);
  initializeInterrupt(STOP_START_PIN, LOW);
  initializeInterrupt(TEAM_ONE_PIN, LOW);
  initializeInterrupt(TEAM_TWO_PIN, LOW);
  initializeInterrupt(NEXT_PIN, LOW);
  
  game.view->setTeamScores(game.teamOneScore, game.teamTwoScore);
}

void clearEvents() {
  game.events[TEAM_ONE_SCORE_EVENT] = 0;
  game.events[TEAM_TWO_SCORE_EVENT] = 0;
  game.events[CATEGORY_EVENT]       = 0;
  game.events[STOP_START_EVENT]     = 0;
  game.events[NEXT_EVENT]           = 0;
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
  game.events[TEAM_ONE_SCORE_EVENT] = digitalRead(TEAM_ONE_PIN)   == LOW;
  game.events[TEAM_TWO_SCORE_EVENT] = digitalRead(TEAM_TWO_PIN)   == LOW;
  game.events[CATEGORY_EVENT]       = digitalRead(CATEGORY_PIN)   == LOW;
  game.events[STOP_START_EVENT]     = digitalRead(STOP_START_PIN) == LOW;
  game.events[NEXT_EVENT]           = digitalRead(NEXT_PIN)       == LOW;
}

void transitionToStarted() {
  clearEvents();
  game.currentState = STARTED;
}

void transitionToGameOver() {
  clearEvents();
  game.currentMessage = game.teamOneScore == POINTS_WIN ? TEAM_ONE_WIN : TEAM_TWO_WIN;
  game.currentState = GAME_OVER;
}

void transitionToStopped() {
  clearEvents();
  game.currentState = STOPPED;
}

void incrementTeamOneScore() {
  clearEvents();
  game.teamOneScore++;
}

void incrementTeamTwoScore() {
  clearEvents();
  game.teamTwoScore++;
}

String nextPhrase() {
  return EMPTY;
}

String nextCategory() {
  return EMPTY;
}

bool gameIsWon() {
  clearEvents();
  return game.teamOneScore == POINTS_WIN || game.teamTwoScore == POINTS_WIN;
}

void clearScores() {
  game.teamOneScore = game.teamTwoScore = 0;
}

void clearPhrase() {
  game.currentMessage = EMPTY;
}

bool startNewGame() {
  return game.events[CATEGORY_EVENT] || game.events[STOP_START_EVENT];
}

void loop() {

  switch(game.currentState) {
    case GAME_OVER:
      if(startNewGame()) {
        clearPhrase();
        clearScores();
        transitionToStopped();
      }
  
      break;
    case STOPPED:
      if(game.events[TEAM_ONE_SCORE_EVENT]) {
        incrementTeamOneScore();
      } else if(game.events[TEAM_TWO_SCORE_EVENT]) {
        incrementTeamTwoScore();
      } else if(game.events[STOP_START_EVENT]) {
        transitionToStarted();
      } else if(game.events[CATEGORY_EVENT]) {
        
      }

      if(gameIsWon()) {
        transitionToGameOver();
      }
      
      break;
    case STARTED:
      if(game.events[STOP_START_EVENT]) {
        transitionToStopped();
      } else if(game.events[NEXT_EVENT]) {
        nextPhrase();
      }
   
      break;
  } 

  game.view->setPhrase(game.currentMessage);
  game.view->setTeamScores(game.teamOneScore, game.teamTwoScore);
}
