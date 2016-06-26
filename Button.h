
class Button {

	private:
		const int PIN = 2;

		int state = LOW;

	protected:
		bool isHigh() {
			return digitalRead(PIN) == HIGH;
		}

	public:
		Button() {
			pinMode(PIN, INPUT);
		}

		bool isPressed() {
			return isHigh();
		}
};
