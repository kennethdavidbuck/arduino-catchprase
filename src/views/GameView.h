#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <LiquidCrystal.h>

class GameView : public LiquidCrystal {

	static const uint8_t ROW_COUNT = 2;
	static const uint8_t COLUMN_COUNT = 16;

	uint8_t firstRow() {
		return 0;
	}

	uint8_t lastRow() {
		return ROW_COUNT - 1;
	}

	uint8_t firstColumn() {
		return 0;
	}

	uint8_t lastColumn() {
		return COLUMN_COUNT - 1;
	}

	public:

		GameView() : LiquidCrystal (7, 8, 9, 10, 11, 12) {
			this->begin(COLUMN_COUNT, ROW_COUNT);
		}

		void setPhrase(String phrase) {
			this->setCursor(firstColumn(), lastRow());
			this->print(phrase);
		}

		void setTeamScores(uint8_t teamOneScore, uint8_t teamTwoScore) {
			this->setTeamOneScore(teamOneScore);
			this->setTeamTwoScore(teamTwoScore);
		}

		void setTeamOneScore(uint8_t score) {
			this->setCursor(firstColumn(), firstRow());
			this->print(score);
		}

		void setTeamTwoScore(uint8_t score) {
			this->setCursor(lastColumn(), firstRow());
			this->print(score);
		}
};

#endif