#ifndef TEAMMODEL_H
#define TEAMMODEL_H

class TeamModel {

	uint8_t score = 0;

	public:
		void incrementScore() {
			this->score += 1;
		}

		uint8_t getScore() {
			return this->score;
		}

		void resetScore() {
			this->score = 0;
		}
};

#endif