#include "Button.h"
#include "GameView.h"
#include "TeamModel.h"

class GameController {

	private:
		GameView* view;
		TeamModel* team1;
		TeamModel* team2;

		Button* categoryButton;
		Button* stopStartButton;
		Button* nextButton;
		Button* team1IncrementScoreButton;
		Button* team2IncrementScoreButton;

	public:
		GameController() {
			categoryButton = new Button();
			nextButton = new Button();
			team1IncrementScoreButton = new Button();
			team2IncrementScoreButton = new Button();
			stopStartButton = new Button();

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
