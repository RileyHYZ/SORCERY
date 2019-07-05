#ifndef __OBJECT_H__
#define __OBJECT_H__

class Observer {
	public:
		virtual void notify()=0;
		virtual ~Observer()=0;
};

#endif