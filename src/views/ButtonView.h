#ifndef BUTTONVIEW_H
#define BUTTONVIEW_H

#include "../interfaces/ObservableInterface.h"
#include "../interfaces/ObserverInterface.h"

class ButtonView : public ObservableInterface {

	static ButtonView *buttonInstance;

	static const int PIN = 2;
	int state = LOW;

	ObserverInterface * observer = 0;

	long unsigned time = 0;

	ButtonView() {
		pinMode(PIN, INPUT_PULLUP);
		attachInterrupt(digitalPinToInterrupt(PIN), handle, RISING);
	}

	public:

		static ButtonView *instance() {
			if(!buttonInstance) {
				buttonInstance = new ButtonView;
			}

			return buttonInstance;
		}

		static void handle() {
			instance()->setState(digitalRead(PIN));
			instance()->notifyObservers();
		}

		void attach(ObserverInterface *observer) {
			this->observer = observer;
		}

		void notifyObservers() {
			if(this->observer) {
				this->observer->notify(this);
			}
		}

		bool isPressed() {
			return state == HIGH;
		}

		void setState(int state) {
			this->state = state;
		}
};

ButtonView *ButtonView::buttonInstance = 0;

#endif
