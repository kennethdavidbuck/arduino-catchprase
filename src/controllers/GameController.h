#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../models/TeamModel.h"
#include "../views/ButtonView.h"
#include "../views/GameView.h"

class GameController {

	private:
		TeamModel* team1;
		TeamModel* team2;

		Button* categoryButton;
		Button* stopStartButton;
		Button* nextButton;
		Button* team1IncrementScoreButton;
		Button* team2IncrementScoreButton;

		GameView* view;

		bool isPressed = true;

	public:
		GameController() {
			// create instances
			team1 = new TeamModel();
			team2 = new TeamModel();

			categoryButton = new Button();
			nextButton = new Button();
			team1IncrementScoreButton = new Button();
			team2IncrementScoreButton = new Button();
			stopStartButton = new Button();

			view = new GameView();

			view->setPhrase("Hello World!");
		}

		void loop() {
			if(!isPressed && nextButton->isPressed()) {
				isPressed = true;
				team1->incrementScore();
			} else if(isPressed && !nextButton->isPressed()) {
				isPressed = false;
			}

			view->setScores(team1->getScore(), team2->getScore());
		}
};

#endif
