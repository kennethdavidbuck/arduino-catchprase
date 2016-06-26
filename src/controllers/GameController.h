#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../models/TeamModel.h"
#include "../views/ButtonView.h"
#include "../views/GameView.h"

class GameController {

	private:
		TeamModel* teamOne;
		TeamModel* teamTwo;

		Button* categoryButton;
		Button* stopStartButton;
		Button* nextButton;
		Button* teamOneIncrementScoreButton;
		Button* teamTwoIncrementScoreButton;

		GameView* view;

		bool isPressed = false;

	public:
		GameController() {
			// create instances
			teamOne = new TeamModel();
			teamTwo = new TeamModel();

			categoryButton = new Button();
			nextButton = new Button();
			teamOneIncrementScoreButton = new Button();
			teamTwoIncrementScoreButton = new Button();
			stopStartButton = new Button();

			view = new GameView();

			view->setScores(teamOne->getScore(), teamTwo->getScore());
			view->setPhrase("Hello World!");
		}

		void loop() {
			if(!isPressed && nextButton->isPressed()) {
				isPressed = true;
				teamOne->incrementScore();
				view->setTeamOneScore(teamOne->getScore());
			} else if(!nextButton->isPressed()) {
				isPressed = false;
			}
		}
};

#endif
