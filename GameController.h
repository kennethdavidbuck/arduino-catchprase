#include "Button.h"
#include "GameView.h"
#include "TeamModel.h"

class GameController {

	private:
		GameView* view;
		TeamModel* team1;
		TeamModel* team2;

		Button* nextButton;

	public:
		GameController() {
			nextButton = new Button();

			team1 = new TeamModel();
			team2 = new TeamModel();
			view = new GameView();
		}

		void loop() {
			if(nextButton->isPressed()) {
				team1->incrementScore();
			}

			view->setScores(team1->getScore(), team2->getScore());
			view->setPhrase("Hello World!");
		}
};
