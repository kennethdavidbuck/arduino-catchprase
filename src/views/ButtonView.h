#ifndef BUTTONVIEW_H
#define BUTTONVIEW_H

class ButtonView {

	private:
		static ButtonView *buttonInstance;

		ButtonView() {
			pinMode(PIN, INPUT);
		}

		const int PIN = 2;

		bool isHigh() {
			return digitalRead(PIN) == HIGH;
		}

	public:

		bool isPressed() {
			return isHigh();
		}

		static ButtonView *instance() {
			if(!buttonInstance) {
				buttonInstance = new ButtonView;
			}

			return buttonInstance;
		}
};

ButtonView *ButtonView::buttonInstance = 0;

#endif
