#ifndef OBSERVER_INTERFACE_H
#define OBSERVER_INTERFACE_H

#include "ObservableInterface.h"

class ObserverInterface {

	public:

		virtual void notify(ObservableInterface *observable) = 0;
};

#endif