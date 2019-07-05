#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector>
#include "observer.h"

class Subject {
    std::vector<Observer*> observers;

  public:
		Subject();
		void attach(Observer*);
		void detach(Observer*);
		void notifyObserver();
		virtual ~Subject();
};

#endif 