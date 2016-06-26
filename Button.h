
class Button {

	private:
		int state = LOW;
		int pin = 2;

	public:
		Button() {
			pinMode(pin, INPUT);
		}

		bool isPressed() {
			return digitalRead(pin) == HIGH;
		}
};