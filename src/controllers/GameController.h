#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../models/TeamModel.h"
#include "../views/ButtonView.h"
#include "../views/GameView.h"

class GameController {

	private:
		TeamModel* teamOne;
		TeamModel* teamTwo;

		ButtonView* teamOneScoreButtonView;

		GameView* view;

		bool isPressed = false;

	public:
		GameController() {
			// create instances
			teamOne = new TeamModel();
			teamTwo = new TeamModel();

			teamOneScoreButtonView = ButtonView::instance();

			view = new GameView();

			view->setScores(teamOne->getScore(), teamTwo->getScore());
			view->setPhrase("Hello World!");
		}

		void loop() {
			if(!isPressed && teamOneScoreButtonView->isPressed()) {
				isPressed = true;
				teamOne->incrementScore();
				view->setTeamOneScore(teamOne->getScore());
			} else if(isPressed && !teamOneScoreButtonView->isPressed()) {
				isPressed = false;
			}
		}
};

#endif
