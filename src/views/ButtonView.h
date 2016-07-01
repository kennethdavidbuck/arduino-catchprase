#ifndef BUTTON_VIEW_H
#define BUTTON_VIEW_H

#include "../interfaces/ObservableInterface.h"
#include "../interfaces/ObserverInterface.h"

class ButtonView : public ObservableInterface {

	static ButtonView *buttonInstance;

	const int PIN = 2;
	int state = HIGH;

	ObserverInterface * observer = 0;

	long unsigned time = 0;

	ButtonView() {
		pinMode(PIN, INPUT_PULLUP);
		attachInterrupt(digitalPinToInterrupt(PIN), handle, LOW);
	}

	public:

		static ButtonView *instance() {
			if(!buttonInstance) {
				buttonInstance = new ButtonView;
			}

			return buttonInstance;
		}

		static void handle() {
			instance()->updateState();
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
			return this->state == LOW;
		}

		void updateState() {
			this->state = digitalRead(PIN);
		}
};

ButtonView *ButtonView::buttonInstance = 0;

#endif
