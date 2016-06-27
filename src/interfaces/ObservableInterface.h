#ifndef OBSERVABLEINTERFACE_H
#define OBSERVABLEINTERFACE_H

class ObserverInterface;

class ObservableInterface {

	public:

		virtual void attach(ObserverInterface *observer) = 0;

		virtual void notifyObservers() = 0;
};

#endif