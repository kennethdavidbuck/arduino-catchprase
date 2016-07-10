
#include "CatchPhrase.h"
#include "Constants.h"
#include "GameView.h"
#include "Pitches.h"

typedef struct Game {
  volatile int events[5] = {0, 0, 0, 0, 0};
  String message         = MESSAGE_EMPTY;
  int state              = STATE_STOPPED;
  int teamOneScore       = 0;
  int teamTwoScore       = 0;
  int categoryIndex      = 0;
  int phraseIndex        = 0;
  GameView *view         = new GameView();
};

// Create the game.
volatile unsigned long lastMicros = 0;
Game game;

void setup() {
  initializeInterrupt(PIN_CATEGORY, LOW);
  initializeInterrupt(PIN_STOP_START, LOW);
  initializeInterrupt(PIN_TEAM_ONE, LOW);
  initializeInterrupt(PIN_TEAM_TWO, LOW);
  initializeInterrupt(PIN_NEXT, LOW);
}

void clearEvents() {
  game.events[EVENT_TEAM_ONE_SCORE] = 0;
  game.events[EVENT_TEAM_TWO_SCORE] = 0;
  game.events[EVENT_CATEGORY]       = 0;
  game.events[EVENT_STOP_START]     = 0;
  game.events[EVENT_NEXT]           = 0;
}

void initializeInterrupt(int pin, int state) {
  attachInterrupt(digitalPinToInterrupt(pin), debounceHandler, state);
  pinMode(pin, INPUT_PULLUP);
}

void debounceHandler() {
  unsigned long currentMicros = (long) micros();
  
  if(currentMicros - lastMicros >= TIMER_DEBOUNCE) {
    handler();
    lastMicros = currentMicros;
  }  
}

void handler() {
  game.events[EVENT_TEAM_ONE_SCORE] = digitalRead(PIN_TEAM_ONE)   == LOW;
  game.events[EVENT_TEAM_TWO_SCORE] = digitalRead(PIN_TEAM_TWO)   == LOW;
  game.events[EVENT_CATEGORY]       = digitalRead(PIN_CATEGORY)   == LOW;
  game.events[EVENT_STOP_START]     = digitalRead(PIN_STOP_START) == LOW;
  game.events[EVENT_NEXT]           = digitalRead(PIN_NEXT)       == LOW;
}

void transitionToStarted() {
  clearEvents();
  game.state = STATE_STARTED;
}

void transitionToGameOver() {
  clearEvents();
  game.message = game.teamOneScore == POINTS_WIN ? MESSAGE_TEAM_ONE_WIN : MESSAGE_TEAM_TWO_WIN;
  game.state   = STATE_OVER;
}

void transitionToStopped() {
  clearEvents();
  game.state = STATE_STOPPED;
}

void playTeamOneSound() {
  tone(PIN_SPEAKER, NOTE_TEAM_ONE, 1000 / INCREMENT_DURATION);
}

void playTeamTwoSound() {
  tone(PIN_SPEAKER, NOTE_TEAM_TWO, 1000 / INCREMENT_DURATION);
}

void incrementTeamOneScore() {
  clearEvents();
  playTeamOneSound();
  game.teamOneScore++;
}

void incrementTeamTwoScore() {
  clearEvents();
  playTeamTwoSound();
  game.teamTwoScore++;
}

String nextPhrase() {
  clearEvents();
  return MESSAGE_EMPTY;
}

String nextCategory() {
  clearEvents();
  return MESSAGE_EMPTY;
}

bool gameIsWon() {
  clearEvents();
  return game.teamOneScore == POINTS_WIN || game.teamTwoScore == POINTS_WIN;
}

void clearScores() {
  game.teamOneScore = game.teamTwoScore = 0;
}

void clearPhrase() {
  game.message = MESSAGE_EMPTY;
}

bool startNewGame() {
  return game.events[EVENT_CATEGORY] || game.events[EVENT_STOP_START];
}

void loop() {
  switch(game.state) {
    case STATE_OVER:
      if(startNewGame()) {
        clearPhrase();
        clearScores();
        transitionToStopped();
      }
  
      break;
    case STATE_STOPPED:
      if(game.events[EVENT_TEAM_ONE_SCORE]) {
        incrementTeamOneScore();
      } else if(game.events[EVENT_TEAM_TWO_SCORE]) {
        incrementTeamTwoScore();
      } else if(game.events[EVENT_STOP_START]) {
        transitionToStarted();
      } else if(game.events[EVENT_CATEGORY]) {
        
      }

      if(gameIsWon()) {
        transitionToGameOver();
      }
      
      break;
    case STATE_STARTED:
      if(game.events[EVENT_STOP_START]) {
        transitionToStopped();
      } else if(game.events[EVENT_NEXT]) {
        nextPhrase();
      }
   
      break;
  } 

  game.view->setPhrase(game.message);
  game.view->setTeamScores(game.teamOneScore, game.teamTwoScore);
}
