#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "../models/TeamModel.h"
#include "../interfaces/ObserverInterface.h"
#include "../interfaces/ObservableInterface.h"
#include "../views/ButtonView.h"
#include "../views/GameView.h"

class GameController : public ObserverInterface {

	TeamModel* teamOne;

	TeamModel* teamTwo;

	ButtonView* teamOneScoreButtonView;

	GameView* view;

	public:

		GameController() {
			this->teamOne = new TeamModel();
			this->teamTwo = new TeamModel();

			this->teamOneScoreButtonView = ButtonView::instance();

			this->view = new GameView();

			this->teamOneScoreButtonView->attach(this);
		}

		void notify(ObservableInterface *observable) {
			if(observable == this->teamOneScoreButtonView) {
				this->handleTeamOneScoreButton((ButtonView*) observable);
			}
		}

		void handleTeamOneScoreButton(ButtonView *button) {
			if(button->isPressed()) {
				this->teamOne->incrementScore();
			}
		}

		void loop() {
			this->view->setPhrase("hello world!");
			this->view->setTeamOneScore(teamOne->getScore());
		}
};

#endif
