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

		void setScores(uint8_t team1Score, uint8_t team2Score) {
			setTeam1Score(team1Score);
			setTeam2Score(team2Score);
		}

		void setTeam1Score(uint8_t score) {
			setCursor(firstColumn(), firstRow());
			print(score);
		}

		void setTeam2Score(uint8_t score) {
			setCursor(lastColumn(), firstRow());
			print(score);
		}
};