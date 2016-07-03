#ifndef CATCH_PHRASE_H
#define CATCH_PHRASE_H

/**
 *
 */
void initializeInterrupt(int pin);

/**
 *
 */
bool buttonIsPressed(int pin);

/**
 *
 */
void handler();

/**
 *
 */
void debounceHandler();

#endif