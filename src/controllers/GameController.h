#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

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

	volatile bool isPressed = false;

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
			if(!this->isPressed && button->isPressed()) {
				this->isPressed = true;
				this->teamOne->incrementScore();
				this->view->setTeamOneScore(teamOne->getScore());
			} else if(this->isPressed && !button->isPressed()) {
				this->isPressed = false;
			}
		}

		void loop() {}
};

#endif
