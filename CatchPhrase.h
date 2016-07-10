#ifndef CATCH_PHRASE_H
#define CATCH_PHRASE_H

void attachStopStartInterrupt();

void attachInterrupts();

void detachInterrupts();

void initializeInterrupt(int pin, int state);

void debounceHandler();

void handler();

void transitionToStarted();

void transitionToGameOver();

void transitionToStopped();

void playTeamOneSound();

void playTeamTwoSound();

void playClockTock();

void playClockTalk();

void incrementTeamOneScore();

void incrementTeamTwoScore();

String nextPhrase();

String nextCategory();

bool gameIsWon();

void clearScores();

void clearPhrase();

bool startNewGame();

#endif