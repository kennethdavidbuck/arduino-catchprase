
#include "CatchPhrase.h"
#include "Constants.h"
#include "GameView.h"
#include "Pitches.h"
#include <SoftwareSerial.h>

#define RX  15
#define TX  16

SoftwareSerial CatchPhrase(RX, TX);

typedef struct GameClock {
  unsigned long lastMillis = -1;
  int tickTock             = TIMER_TICK;
};

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

volatile unsigned long lastDebounceMillis = 0;

// Create the game.
GameClock gameClock;
Game game;

void setup() {
  // we wont be toggling the stop/start pin, so we attach the interrupt here once.
  CatchPhrase.begin(9600);
  
  attachStopStartInterrupt();
  transitionToStopped();
}

void attachStopStartInterrupt() {
  attachInterrupt(digitalPinToInterrupt(PIN_STOP_START), debounceHandler, LOW);
  pinMode(PIN_STOP_START, INPUT_PULLUP);
}

void attachInterrupts() {
  for(int i = 0; i < PINS_LENGTH; i += 1) {
    attachInterrupt(digitalPinToInterrupt(PINS[i]), debounceHandler, LOW);
    pinMode(PINS[i], INPUT_PULLUP);
  }
}

void detachInterrupts() {
  for(int i = 0; i < PINS_LENGTH; i += 1) {
    detachInterrupt(digitalPinToInterrupt(PINS[i]));
  }
}

void clearEvents() {
  for(int i = 0; i < EVENTS_LENGTH; i += 1) {
    game.events[i] = 0;
  }
}

void debounceHandler() {
  unsigned long currentMillis = (long) millis();
  
  if(currentMillis - lastDebounceMillis >= TIMER_DEBOUNCE) {
    handler();
    lastDebounceMillis = currentMillis;
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
  gameClock.tickTock    = TIMER_TICK;
  gameClock.lastMillis  = TIMER_NEW_ROUND;
  game.state            = STATE_STARTED;
  detachInterrupts();
}

void transitionToStopped() {
  clearEvents();
  game.state  = STATE_STOPPED;
  attachInterrupts();
}

void transitionToGameOver() {
  clearEvents();
  game.message = game.teamOneScore == POINTS_WIN ? MESSAGE_TEAM_ONE_WIN : MESSAGE_TEAM_TWO_WIN;
  game.state   = STATE_OVER;
  attachInterrupts();
}

void playTeamOneSound() {
  tone(PIN_SPEAKER, NOTE_TEAM_ONE, 1000 / INCREMENT_DURATION);
}

void playTeamTwoSound() {
  tone(PIN_SPEAKER, NOTE_TEAM_TWO, 1000 / INCREMENT_DURATION);
}

void playClockTick() {
  tone(PIN_SPEAKER, NOTE_CLOCK_TICK, 1000 / INCREMENT_DURATION);
}

void playClockTock() {
  tone(PIN_SPEAKER, NOTE_CLOCK_TOCK, 1000 / INCREMENT_DURATION);
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

void updateClock() {
  unsigned long currentMillis = millis();
  unsigned long timeDifference = currentMillis - gameClock.lastMillis;
  
  if(gameClock.lastMillis == TIMER_NEW_ROUND || timeDifference > 500) {
    if(gameClock.tickTock == TIMER_TICK) {
      gameClock.tickTock = TIMER_TOCK;
      playClockTick();
      CatchPhrase.println("TICK ");
    } else {
      gameClock.tickTock = TIMER_TICK;
      CatchPhrase.println("TOCK ");
      playClockTock();
    }
    
    gameClock.lastMillis = currentMillis;
  }
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
        nextCategory();
      }

      if(gameIsWon()) {
        transitionToGameOver();
      }
      
      break;
    case STATE_STARTED:
      updateClock();
      
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
