#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <LiquidCrystal.h>

class GameView : public LiquidCrystal {

	private:

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
			begin(COLUMN_COUNT, ROW_COUNT);
		}

		void setPhrase(String phrase) {
			setCursor(firstColumn(), lastRow());
			print(phrase);
		}

		void setScores(uint8_t teamOneScore, uint8_t teamTwoScore) {
			setTeamOneScore(teamOneScore);
			setTeamTwoScore(teamTwoScore);
		}

		void setTeamOneScore(uint8_t score) {
			setCursor(firstColumn(), firstRow());
			print(score);
		}

		void setTeamTwoScore(uint8_t score) {
			setCursor(lastColumn(), firstRow());
			print(score);
		}
};

#endif