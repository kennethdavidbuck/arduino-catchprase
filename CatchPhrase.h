#ifndef CATCH_PHRASE_H
#define CATCH_PHRASE_H

void initializeInterrupt(int pin, int state);

void debounceHandler();

void handler();

void transitionToStarted();

void transitionToGameOver();

void transitionToStopped();

void playTeamOneSound();

void playTeamTwoSound();

void incrementTeamOneScore();

void incrementTeamTwoScore();

String nextPhrase();

String nextCategory();

bool gameIsWon();

void clearScores();

void clearPhrase();

bool startNewGame();

#endif