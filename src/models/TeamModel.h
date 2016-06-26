#ifndef TEAMMODEL_H
#define TEAMMODEL_H

class TeamModel {

	private:
		uint8_t score = 0;

	public:
		void incrementScore() {
			score += 1;
		}

		uint8_t getScore() {
			return score;
		}

		void resetScore() {
			score = 0;
		}
};

#endif