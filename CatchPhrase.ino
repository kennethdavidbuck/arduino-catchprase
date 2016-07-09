
#include "CatchPhrase.h"
#include "GameView.h"

//
#define DEBOUNCE_TIME         100000
#define POINTS_WIN            7

// interrupt pins
#define CATEGORY_PIN          0
#define STOP_START_PIN        1
#define TEAM_ONE_PIN          2
#define TEAM_TWO_PIN          3
#define NEXT_PIN              7

// sound pins
#define SPEAKER_PIN           5

// sound notes
#define C1_NOTE               33

// game sound notes
#define INCREMENT_NOTE        C1_NOTE

// sound durations
#define INCREMENT_DURATION    16

// game messages
#define EMPTY                  "                "
#define TEAM_ONE_WIN           " TEAM ONE WINS! "
#define TEAM_TWO_WIN           " TEAM TWO WINS! "
#define SUCCESS                "    SUCCESS!    "

// game states
#define OVER_STATE            0
#define STOPPED_STATE         1
#define STARTED_STATE         2

// game events
#define TEAM_ONE_SCORE_EVENT  0
#define TEAM_TWO_SCORE_EVENT  1
#define CATEGORY_EVENT        2
#define STOP_START_EVENT      3
#define NEXT_EVENT            4

// game
typedef struct Game {
  volatile int events[5]      = {0, 0, 0, 0, 0};
  String message              = EMPTY;
  int state                   = STOPPED_STATE;
  int teamOneScore            = 0;
  int teamTwoScore            = 0;
  int categoryIndex           = 0;
  int phraseIndex             = 0;
  GameView *view              = new GameView();
};

// Create the game.
volatile unsigned long lastMicros = 0;
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
  game.state = STARTED_STATE;
}

void transitionToGameOver() {
  clearEvents();
  game.message = game.teamOneScore == POINTS_WIN ? TEAM_ONE_WIN : TEAM_TWO_WIN;
  game.state   = OVER_STATE;
}

void transitionToStopped() {
  clearEvents();
  game.state = STOPPED_STATE;
}

void playIncrementScoreSound() {
  tone(SPEAKER_PIN, INCREMENT_NOTE, 1000 / INCREMENT_DURATION);
}

void incrementTeamOneScore() {
  clearEvents();
  playIncrementScoreSound();
  game.teamOneScore++;
}

void incrementTeamTwoScore() {
  clearEvents();
  playIncrementScoreSound();
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
  game.message = EMPTY;
}

bool startNewGame() {
  return game.events[CATEGORY_EVENT] || game.events[STOP_START_EVENT];
}

void loop() {

  switch(game.state) {
    case OVER_STATE:
      if(startNewGame()) {
        clearPhrase();
        clearScores();
        transitionToStopped();
      }
  
      break;
    case STOPPED_STATE:
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
    case STARTED_STATE:
      if(game.events[STOP_START_EVENT]) {
        transitionToStopped();
      } else if(game.events[NEXT_EVENT]) {
        nextPhrase();
      }
   
      break;
  } 

  game.view->setPhrase(game.message);
  game.view->setTeamScores(game.teamOneScore, game.teamTwoScore);
}
