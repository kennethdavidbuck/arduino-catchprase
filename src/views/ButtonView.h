#ifndef BUTTON_VIEW_H
#define BUTTON_VIEW_H

#include "../interfaces/ObservableInterface.h"
#include "../interfaces/ObserverInterface.h"

class ButtonView : public ObservableInterface {

	static ButtonView *buttonInstance;

	const int PIN = 2;
	int state = HIGH;

	ObserverInterface * observer = 0;

	ButtonView() {
		pinMode(PIN, INPUT_PULLUP);
		attachInterrupt(digitalPinToInterrupt(PIN), debounceHandler, FALLING);
	}

	public:
		static volatile unsigned long lastMicros;
		static unsigned long debounceTime;

		static ButtonView *instance() {
			if(!buttonInstance) {
				buttonInstance = new ButtonView;
			}

			return buttonInstance;
		}

		static void debounceHandler() {
			if((long)(micros() - lastMicros) >= debounceTime * 1000) {
				handle();
				lastMicros = micros();
			}
		}

		static void handle() {
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
			return digitalRead(PIN) == LOW;
		}
};

unsigned long ButtonView::debounceTime = 100;

volatile unsigned long ButtonView::lastMicros = 0;

ButtonView *ButtonView::buttonInstance = 0;

#endif
