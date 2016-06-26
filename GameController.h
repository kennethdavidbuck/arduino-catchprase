#include "TeamModel.h"
#include "GameView.h"

class GameController {

	private:
		GameView* view;
		TeamModel* team1;
		TeamModel* team2;

	public:
		GameController() {
			team1 = new TeamModel();
			team2 = new TeamModel();
			view = new GameView();

			view->setScores(team1->getScore(), team2->getScore());
			view->setPhrase("Hello World!");
		}

		void loop() {

		}
};
