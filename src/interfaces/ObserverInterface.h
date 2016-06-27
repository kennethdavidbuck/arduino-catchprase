#ifndef OBSERVERINTERFACE_H
#define OBSERVERINTERFACE_H

#include "ObservableInterface.h"

class ObserverInterface {

	public:

		virtual void notify(ObservableInterface *observable) = 0;
};

#endif