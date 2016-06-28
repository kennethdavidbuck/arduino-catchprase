#ifndef OBSERVABLE_INTERFACE_H
#define OBSERVABLE_INTERFACE_H

class ObserverInterface;

class ObservableInterface {

	public:

		virtual void attach(ObserverInterface *observer) = 0;

		virtual void notifyObservers() = 0;
};

#endif