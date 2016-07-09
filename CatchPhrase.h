#ifndef CATCH_PHRASE_H
#define CATCH_PHRASE_H

/**
 *
 */
void initializeInterrupt(int pin);

/**
 *
 */
bool isKeyPressEvent(int pin);

/**
 *
 */
void handler();

/**
 *
 */
void debounceHandler();


/**
 *
 */
void clearEvents();

#endif