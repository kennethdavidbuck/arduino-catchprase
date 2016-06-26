#ifndef BUTTONVIEW_H
#define BUTTONVIEW_H

class Button {

	private:
		const int PIN = 2;

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

#endif
