
#include "./src/controllers/GameController.h"

static GameController* game;

void setup() {
  game = new GameController();
}

void loop() {
  game->loop();
}

